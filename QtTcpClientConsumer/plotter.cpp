#include "plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

using namespace std;

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    fundo.setRgb(255,255,0);
}

void Plotter::paintEvent(QPaintEvent *e)
{
    int x1, y1, x2, y2;

     // cria um objeto pintor
     QPainter p(this);

     // faz com que a linha seja desenhada
     // com tracos suaves
     p.setRenderHint(QPainter::Antialiasing);

     // cria um objeto de caneta
     QPen pen;
     // cria um objeto de pincel
     QBrush brush;
     // define a cor da caneta
     pen.setColor(QColor(255,0,0));
     pen.setWidth(2);

     // informa ao painter qual a caneta a ser
     // usada
     p.setPen(pen);

     // define a cor do pincel
     brush.setColor(fundo);
     brush.setStyle(Qt::SolidPattern);

     // informa oa painter qual o pincel a ser
     // usado
     p.setBrush(brush);
     p.drawRect(0,0,width(),height());
     // (x1,y1) -> (x2,y2)
     pen.setColor(QColor(0,0,255));
     p.setPen(pen);
     // desenha a linha do eixo de coordenadas
     p.drawLine(0,height(),width(),height());
     /*x1 = 0;
     x2 = width();
     y2 = y1 = height()/2;
     p.drawLine(x1, y1, x2, y2);*/

}

void Plotter::load(vector<int> posicao, vector<int> tempo)
{
    int itP, itT;
    itP = posicao.size();
    itF = tempo.size();

    for(int i = 0; i < itP; i++){
        if(itP <=  width()){
            //p.drawLine(tempo[i], y1, x2, y2);
        }
    }
}
