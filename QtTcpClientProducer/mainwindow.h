#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  
private:
  int min, max, interval;
  QString ip = "127.0.0.1";
  //QTime timer;
  int timer;
  bool timeActive = false;

public slots:
  void putData();
  void tcpConnect();
  void changeMin(int min);
  void changeMax(int max);
  void setTimer(int interval);
  void desconnect();
  void start();
  void stop();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  void timerEvent(QTimerEvent *e);
};

#endif // MAINWINDOW_H
