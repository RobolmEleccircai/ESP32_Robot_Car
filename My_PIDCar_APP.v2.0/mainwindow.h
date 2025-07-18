#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QBluetoothSocket>
#include <QMessageBox>
#include <QListWidgetItem>

//#include <QtBluetooth/qtbluetoothglobal.h>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>

#include <QTextCodec>
#include <QDateTime>
#include <QTimer>//定时器
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void blueStates();
private slots:
     void on_pushButton_openBLE_clicked();
     void on_pushButton_upDateBLE_clicked();
     void addBlueToothDevicesToList(const QBluetoothDeviceInfo &info);
     void findFinish();
     void connectBLE(QListWidgetItem *item);
     void connectOK();
     void connectNot();
     void readBluetoothDataEvent();

     void on_pushButton_back_clicked();
     void on_pushButton_stop_clicked();

     void on_pushButton_closeBLE_clicked();
     void on_pushButton_clearReceive_clicked();

     void on_pushButton_kd_raise_clicked();

     void on_pushButton_kd_reduce_clicked();

     void on_pushButton_fornt_clicked();

     void on_pushButton_kp_raise_clicked();

     void on_pushButton_kp_reduce_clicked();

     void on_pushButton_ki_raise_clicked();

     void on_pushButton_ki_reduce_clicked();

private:
    Ui::MainWindow *ui;

        QBluetoothDeviceDiscoveryAgent *discoveryAgent;//用来对周围蓝牙进行搜寻
        QBluetoothLocalDevice *localDevice;//对本地设备进行操作，比如进行设备的打开，设备的关闭等等
        QBluetoothSocket *socket;//就是用来进行蓝牙配对链接和数据传输的
        QTimer *timer;

        QString fornt = "a";
        QString stop = "s";
        QString back = "b";

        QString kp_reduce = "0";
        QString kp_raise = "1";

        QString ki_reduce = "2";
        QString ki_raise = "3";

        QString kd_reduce = "4";
        QString kd_raise = "5";

        QString comStr;

};
#endif // MAINWINDOW_H
