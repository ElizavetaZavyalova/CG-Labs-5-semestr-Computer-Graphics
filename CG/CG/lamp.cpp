#include "lamp.h"
#define MAXINTECITY 1.1
#define MININTECITY 0.1

Lamp::Lamp(QVector3D cordinates,float lightingIntensity){
    this->cordinates=cordinates;
    this->Intensity=lightingIntensity;
    this->colorGlare=QColor(0,255,0);

}

void Lamp::changeIntensity(){
    angle=(angle+1)%360;
}
float Lamp::getIntensity(){
    return Intensity*qSin(qDegreesToRadians(angle));
}
void Lamp::setIntensity(float intensityStep){
    if(Intensity+intensityStep<MAXINTECITY&&Intensity+intensityStep>MININTECITY){
        Intensity+=intensityStep;
    }


}
