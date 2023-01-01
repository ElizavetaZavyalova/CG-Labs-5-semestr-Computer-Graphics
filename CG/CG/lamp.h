#ifndef LAMP_H
#define LAMP_H
#include <QVector3D>
#include <QColor>

class Lamp
{
private:
    int angle=90;
     float Intensity=0.5;
public:
    QColor colorGlare;

public:
    float getIntensity();
    void changeIntensity();
    void setIntensity(float intensityStep);
    QVector3D cordinates;
    Lamp(QVector3D cordinates,float lightingIntensity);

};

#endif // LAMP_H
