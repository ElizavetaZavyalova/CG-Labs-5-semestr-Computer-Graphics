#include "camera.h"

Camera::Camera(float distance)
{
   this->cameraPosiation=distance;
   this->cameraNormal=QVector3D(-1/qSqrt(3),-1/qSqrt(3),1/qSqrt(3));

}
QVector3D Camera::getCameraPosition(){

    return QVector3D(2*cameraPosiation, 1.5*cameraPosiation,0);
}
QVector3D& Camera::getCameraNormal(){

    return this->cameraNormal;
}
void Camera::setcameraPosiation(float position){
    this->cameraPosiation=position;
}
void Camera::setNormal(int proectionValue){
    switch(proectionValue){
    {
        case _X:
            cameraNormal=QVector3D(1,0,0);
            break;
        case X:
             cameraNormal=QVector3D(-1,0,0);
            break;
        case _Y:
             cameraNormal=QVector3D(0,1,0);
            break;
        case Y:
            cameraNormal=QVector3D(0,-1,0);
            break;
        case _Z:
             cameraNormal=QVector3D(0,0,1);
            break;
        case Z:
             cameraNormal=QVector3D(0,0,-1);
            break;
        case Isometry:
             cameraNormal=QVector3D(-1/qSqrt(3),-1/qSqrt(3),1/qSqrt(3));
            break;
    }
    };

}
