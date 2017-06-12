#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(start()));
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->horizontalSliderMin,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(changeMin(int)));
  connect(ui->horizontalSliderMax,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(changeMax(int)));
  connect(ui->horizontalSliderTiming,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setTimer(int)));
  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stop()));
  connect(ui->horizontalSliderTiming,
          SIGNAL(valueChanged(int)),
          ui->labelTiming,
          SLOT(setNum(int)));
  connect(ui->pushButtonDesconect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(desconnect()));


}

void MainWindow::tcpConnect(){
  ip = ui->lineEdit->displayText();
  socket->connectToHost(ip,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
    changeMax(max);
    changeMin(min);
    interval=ui->horizontalSliderTiming->value()*1000;
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::changeMin(int min)
{
    this->min = min;
    if(this->min > max){
        max=min;
        ui->horizontalSliderMax->setValue(min);
    }
}

void MainWindow::changeMax(int max)
{
    this->max = max;
    if(this->max < min){
        ui->horizontalSliderMin->setValue(max);
        min = max;

    }
}

void MainWindow::setTimer(int interval)
{
    this->interval = interval*1000;

}

void MainWindow::desconnect()
{
    if(socket->waitForConnected(3000)){
      qDebug() << "Disconnected";

      if(timeActive){
         timeActive = false;
         killTimer(timer);
      }

      socket->close();
    }
    else{
      qDebug() << "Disconnected";
    }


}

void MainWindow::start()
{
    if(socket->waitForConnected(3000)){
        if(timeActive){
            killTimer(timer);
            timer = startTimer(interval);
        }else {
            timer = startTimer(interval);
            timeActive = true;
        }
      }
      else{
        qDebug() << "Conecte-se";
      }
}

void MainWindow::stop()
{
  if(timeActive){
    killTimer(timer);
    timeActive = false;
  }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(socket->waitForConnected(3000)){
      putData();
    }
    else{
      qDebug() << "Disconnected";
      killTimer(timer);
    }
}


void MainWindow::putData()
{
  QDateTime datetime;
  QString str;
  if(socket->waitForConnected(3000)){
      srand((unsigned)time(0));
      int aleatorio = rand()%(max-min+1) + min;
      if(socket->state()== QAbstractSocket::ConnectedState){
          datetime = QDateTime::currentDateTime();
          str = "set "+
              datetime.toString(Qt::ISODate)+
              " "+
              QString::number(aleatorio )+"\r\n";

          qDebug() << str;
          ui->textEdit->append(str);
          qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
          if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
          }
      }
  }
}
MainWindow::~MainWindow()
{
  killTimer(timer);
  delete socket;
  delete ui;
}
