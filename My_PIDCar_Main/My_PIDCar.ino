#include "BluetoothSerial.h"
#include <MPU6050_tockn.h>
#include <Wire.h>

#define IN1 26
#define IN2 27
#define IN3 32
#define IN4 33

int sda_pin = 13, scl_pin = 15; //自定义eps32的I2C引脚

/*---调试和预设定值的变量--------*/
float Balance_Angle_raw = 0.04;  //测试出的静态机械平衡角度。
int leftMotorPwmOffset = 38, rightMotorPwmOffset = 38; //测试出的左右轮的启动pwm值，pwm达到一定电压马达才开始转动。
float ENERGY = 1.5;                    //设定的前进后退倾倒角度幅度（越大，前冲后退越快）
float kp = 19.00, ki = 1.83, kd = 1.19;     //根据调试测试得到设置kp ki kd的值
/*---调试和预设定的变量 end--------*/

/*---调试和控制变量--------*/ 
float Keep_Angle, bias, integrate;              //保持角度，角度偏差，偏差积分变量
float AngleX, GyroX;                     // mpu6050输出的角度值为浮点数，两位有效小数
int vertical_PWM, PWM, L_PWM, R_PWM;  //各种PWM计算值
/*---调试和控制变量 end--------*/

char flag; //预留标签

BluetoothSerial SerialBT; //实例化esp32的蓝牙串口对象
MPU6050 mpu6050(Wire);    //实例化mpu6050对象

void motor(int left_EN, int right_EN)   //马达输出函数
{
  left_EN = constrain(left_EN, -255, 255);
  right_EN = constrain(right_EN, -255, 255);  //限定PWM区间在-255~255
  if (left_EN >= 0)
  {
    analogWrite(IN1, left_EN);  // 将一个模拟数值写进Arduino引脚，控制电机的转速。
    analogWrite(IN2, 0);  // pin：被读取的模拟引脚号码
                          // value：0到255之间的PWM频率值, 0对应off, 255对应on
  }
  if (left_EN < 0)
  {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0 - left_EN);
  }
  if (right_EN >= 0)
  {
    analogWrite(IN3, right_EN);
    analogWrite(IN4, 0);
  }
  if (right_EN < 0)
  {
    analogWrite(IN3, 0);
    analogWrite(IN4, 0 - right_EN);
  }
}

void serial_debug()   //蓝牙串口调试和控制函数，根据手机端发送来的串口数据调试或控制
{
  if (SerialBT.available() > 0)
  {
    char DATA = SerialBT.read();
    delay(5);
    switch (DATA)
    {

      /*直立环调试*/
      case ' 0':
        kp -= 0.5; //调节直立环 比例kp项-
        break;
      case '1':
        kp += 0.5; //调节直立环 比例kp项+
        break;

      case '2':
        ki -= 0.1; //调节直立环 积分项ki-
        break;
      case '3':
        ki += 0.1; //调节直立环 积分项ki+
        break;
      case '4':
        kd -= 0.1; //调节直立环 微分项kd-
        break;
      case '5':
        kd += 0.1; //调节直立环 微分项kd+
        break;

      /*微小调节*/
      case '6':
        ki -= 0.01; //调节直立环 积分项ki-
        break;
      case '7':
        ki += 0.01; //调节直立环 积分项ki+
        break;
      case '8':
        kd -= 0.01; //调节直立环 微分项kd-
        break;
      case '9':
        kd += 0.01; //调节直立环 微分项kd+
        break;

      /*蓝牙串口控制程序*/
      case 's': //停车
        Keep_Angle = Balance_Angle_raw;  //调节物理平衡点为机械平衡角度值，原地平衡
        break;
      case 'a': //前进
        Keep_Angle = Balance_Angle_raw + ENERGY; //通过设定需保持的倾角，使得小车前进后退
        break;
      case 'b': //后退
        Keep_Angle = Balance_Angle_raw - ENERGY;
        break;
    }

    /*调试时PID极性限制*/
    if (kp < 0)kp = 0;
    if (ki < 0)ki = 0;
    if (kd < 0)kd = 0;

    /*串口打印输出显示*/
    SerialBT.print("Keep_Angle: ");
    SerialBT.println(Keep_Angle);
    SerialBT.print("kp:");
    SerialBT.print(kp);
    SerialBT.print("  ki:");
    SerialBT.print(ki);
    SerialBT.print("  kd:");
    SerialBT.println(kd);

    SerialBT.print("  AngleX:");
    SerialBT.println(AngleX);
    SerialBT.print("  GyroX:");
    SerialBT.println(GyroX); 

    SerialBT.println("--------------------");
  }
}

void vertical_pwm_calculation() //直立PMW计算
{
  AngleX = mpu6050.getAngleX();
  GyroX = mpu6050.getGyroX();
  bias = AngleX - Keep_Angle; // 计算角度偏差。bias为小车角度是静态平衡角度的差值。
  integrate += bias; //偏差的积分，integrate为全局变量，一直积累。
  integrate = constrain(integrate, -1000, 1000); //限定误差积分的最大和最小值
  /*==直立PID计算PWM==通过陀螺仪返回数据计算，前倾陀螺仪Y轴为正，后仰陀螺仪Y轴为负。
    前倾车前进，后仰车后退，保持直立。但可能为了直立，车会随时移动。*/
  vertical_PWM = kp * bias + ki * integrate + kd * GyroX;
}


void motor_control() //马达PWM控制函数
{
  /*---【补偿右轮pwm差值】------------*/
  if (PWM >= 0)
  {
    L_PWM = PWM + leftMotorPwmOffset;  //左右轮的启动pwm达到一定电压马达才开始转动。这里为补偿值。
    R_PWM = PWM + rightMotorPwmOffset; //左右轮的启动pwm达到一定电压马达才开始转动。这里为补偿值。
  }
  if (PWM < 0)
  {
    L_PWM = PWM - leftMotorPwmOffset;  //左右轮的启动pwm达到一定电压马达才开始转动。这里为补偿值。
    R_PWM = PWM - rightMotorPwmOffset; //左右轮的启动pwm达到一定电压马达才开始转动。这里为补偿值。
  }
  if (PWM == 0)
  {
    L_PWM = 0; //
    R_PWM = 0; //
  }


  /*---【控制马达输出】-------------*/
  L_PWM = constrain(L_PWM, -255, 255); //计算出来的PWM限定大小。255为输出上限。
  R_PWM = constrain(R_PWM, -255, 255);

  motor(L_PWM, R_PWM);

  /*--------判断是否小车倒下，此时停止马达和编码器计数-----*/
  if (AngleX > 45 || AngleX < -45) //倾角过大（车倒下时），停止马达输出
  {
    motor(0, 0);
  }
}


void setup() {  //初始化
  SerialBT.begin("ESP32_car"); // Bluetooth device name
  Wire.begin(sda_pin, scl_pin);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
  Keep_Angle = Balance_Angle_raw; //平衡角度初始化为静态平衡时的陀螺仪角度。Keep_Angle可以改变，才可以控制前进后退。
  motor(0, 0);                    //机器启动时马达确保停止。
  delay(10);                      //循环前延时，确保各种初始和准备完成
}

void loop() {
  /*====串口PID调试+控制===*/
  serial_debug();

  /*====陀螺仪刷新===*/
  mpu6050.update();

  /*====PWM计算====*/
  vertical_pwm_calculation(); //直立环PWM计算

  PWM = vertical_PWM;

  /*====马达输出=====*/
  motor_control();
}
