#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QMap>
#include <QTimer>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QPainter>
#include "engine.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    enum proection{Isometry='0',_X='1',X='2',_Y='3',Y='4',_Z='5',Z='6'};
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent*)override;
    void resizeEvent(QResizeEvent*event)override;
    void drowGrafic();
    void drowProection();
    void setIntensity(float intensityStep);
    void setSmoothness(float SmoothnessStep);
    void changeProection(char key);
    QPoint makeProection(QVector3D&Point);
private:
    //void resize()

    void Scale (float   scale);
    void RotateX(float   angle);
    void RotateY(float   angle);
    void RotateZ(float   angle);
    void makeApproximation(int accuracy);
    void RotateVector(QVector3D& vector, float angle);
private:
    QVector2D mousePressPosition;
    QVector2D mouseReleasePosition;
    QTimer *timer;
    Engine* engine=nullptr;
    Figure* figure=nullptr;
    Camera* camera=nullptr;
    Lamp*lamp=nullptr;
    int orintation=1;
    int proectionValue=0;
    int sideProection=0;

private:
    Ui::Widget *ui;
};


#endif // WIDGET_H
