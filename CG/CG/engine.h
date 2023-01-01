#ifndef ENGINE_H
#define ENGINE_H
#include "figure.h"
#include "camera.h"
#include "lamp.h"
#include "shaders.h"
#include <functional>
#include <QMap>

class Engine
{
    int approximation=0;
    Figure* figure=nullptr;
    Camera* camera=nullptr;
    Shaders* shaders=nullptr;
    MatrixAlgorithms* matrix=nullptr;

private:
    QVector3D makeRotateEVector(QVector2D& vector);
    void changeFigureBasis(QVector<QVector3D>& vector);
public:
    void setSinIntensity();
    void setIntensity(float intensityStep);
    void setSmoothness(float SmoothnessStep);
    int getApproximation();
    void makeApproximation(int accuracy);
    void changeBasis(QVector<QVector3D>& vector);
public://scale
    void scaleGeometry(float   scale);
    void makeScale(float   scale);
    void Scale(float   scale);
public://освещение
    QColor makeColor(FigureEdge&edge);
public://drow
    bool IsDraw(QVector3D& cameraView, QVector3D& Normal);
    QPoint Proection(QVector3D& Point, int proectionNumber);
    void setCameraNormal(int proectionNumber);
public://rotate
    void RotateX(float   angle);
    void RotateY(float   angle);
    void RotateZ(float   angle);
    void RotateVector(QVector3D& vector, float angle);
public://set get
    void setFigure(Figure*figure);
    void setLamp(Lamp*lamp);
    void setCamera(Camera*camera);
    Engine(Figure*figure, Camera*camera, Lamp*lamp);
    ~Engine();
};

#endif // ENGINE_H
