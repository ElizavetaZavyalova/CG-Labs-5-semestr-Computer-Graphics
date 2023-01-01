#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>

class Camera
{    enum proection{Isometry='0',_X='1',X='2',_Y='3',Y='4',_Z='5',Z='6'};
protected:
    float cameraPosiation;
    QVector3D cameraNormal;
public:
    QVector3D getCameraPosition();
    QVector3D& getCameraNormal();
    Camera(float distance);
    void setcameraPosiation(float position);
    void setNormal(int proectionValue);

};

#endif // CAMERA_H
