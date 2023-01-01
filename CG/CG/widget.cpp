#include "widget.h"
#include "ui_widget.h"
#include <QPolygon>
#define COUNTPROECTION '7'


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lamp=new Lamp(QVector3D(2*width(), 2*width(),0),0.5);
    camera=new Camera(width());
    figure=new Figure(width()/20.0,width()/10.0,width()/15.0, 6);
    engine=new Engine(figure,camera,lamp);
    this->setStyleSheet("background-color:black;");

}

Widget::~Widget()
{
    delete figure;
    delete engine;
    delete ui;
}

void Widget::resizeEvent(QResizeEvent*event){
    if((event->oldSize().width())==-1){
        return;
    }   
    float scale =(float)width()/((float)((event->oldSize().width())));
    engine->scaleGeometry(scale);
    repaint();
}
void Widget::keyPressEvent(QKeyEvent *event){
     if(isdigit(event->key())&&event->key()<COUNTPROECTION){
         changeProection(event->key());
     }
    switch(event->key()){
    {
        case 'X':
            RotateX((float)orintation);
            break;
        case 'Y':
            RotateY((float)orintation);
            break;
        case 'Z':
            RotateZ((float)orintation);
            break;
        case 'S':
            Scale(1+0.1*(float)orintation);
            break;
        case 'A':
            makeApproximation(orintation);
            break;
        case 'M':
            setSmoothness(0.01*(float)orintation);
            break;
        case'I':
            setIntensity(0.1*(float)orintation);
            break;
        case 61: //'+'
           orintation=1;
            break;
        case 45: //'-'
           orintation=-1;
            break;
    }
    };
}
QPoint Widget::makeProection(QVector3D&Point){
 return engine->Proection(Point, proectionValue);
}

void Widget::changeProection(char key){
    this->proectionValue=key;
    engine->setCameraNormal(key);
    repaint();
}
void Widget::drowProection(){

    const QPoint center(width() / 2.0, height() / 2.0);
    QPainter painter(this);
    painter.setPen(Qt::white);
    //painter.setBrush(Qt::blue);
    QVector<FigureEdge> edges=figure->getEdgesByRef();
     for(int edge=0; edge<edges.size(); edge++){
        if(engine->IsDraw(edges[edge].Normal, camera->getCameraNormal())){
              QPolygon polygon;
              QColor color=engine->makeColor(edges[edge]);
             painter.setPen(color);
             painter.setBrush(color);
             for(int point=0;point<edges[edge].Points.size(); point++){
                 polygon<<makeProection(*edges[edge].Points[point])+center;
             }
             painter.drawPolygon(polygon);
        }
     }
}
void Widget::drowGrafic(){

}
void Widget::paintEvent(QPaintEvent*)
{
 drowProection();

}


void Widget::mousePressEvent(QMouseEvent *event){
    mousePressPosition   = QVector2D(event->position());
}
void Widget::mouseReleaseEvent(QMouseEvent *event){
    mouseReleasePosition = QVector2D(event->position());
}

void Widget::Scale(float   scale){

     engine->Scale(scale);
     repaint();

}
void Widget::RotateX(float   angle){

    engine->RotateX(angle);
    repaint();

}
void Widget::RotateY(float  angle){

    engine->RotateY(angle);
    repaint();

}
void Widget::RotateZ(float   angle){

    engine->RotateZ(angle);
    repaint();

}
void Widget::setIntensity(float intensityStep){

    engine->setIntensity(intensityStep);
    repaint();

}
void Widget::setSmoothness(float SmoothnessStep){

    engine->setSmoothness(SmoothnessStep);
    repaint();

}

void Widget::makeApproximation(int accuracy){

    engine->makeApproximation(accuracy);

    repaint();
}

