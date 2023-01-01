#ifndef SHADERS_H
#define SHADERS_H
#include <QColor>
#include "color.h"
#include "figure.h"
#include "matrix.h"
#include "lamp.h"

class Shaders
{
   Lamp*lamp=nullptr;
   MatrixAlgorithms*matrix=nullptr;
   ColorAlgorithms*color=nullptr;
   float Intancity=0.1;
public:

    QColor makeColor(const FigureEdge&edge, const Texture&texture, QVector3D&cameraPosition);
    QVector3D makeItemDistance(const FigureEdge&edge);
    void setLamp(Lamp*lamp);
    void setIntensity(float intensityStep);
    void setSinIntensity();
    Shaders(MatrixAlgorithms*matrix);
    ~Shaders();
};

#endif // SHADERS_H
