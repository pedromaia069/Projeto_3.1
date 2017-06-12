#ifndef PLOTTER_H
#define PLOTTER_H

#include <QColor>

#include <QWidget>
#include <vector>

using namespace std;
class Plotter : public QWidget
{
    Q_OBJECT

private:
    QColor fundo;
public:
    explicit Plotter(QWidget *parent = 0);
      void paintEvent(QPaintEvent *e);
      //void timerEvent(QTimerEvent *e);
      //void mouseMoveEvent(QMouseEvent *e);
      //void setFundo(int r, int g, int b);

signals:

public slots:
      void load(vector<int> posicao, vector<int> tempo);
};

#endif // PLOTTER_H
