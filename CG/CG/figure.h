#ifndef FIGURE_H
#define FIGURE_H
#include <QVector3D>
#include <QVector>
#include "matrix.h"
#include <QColor>

class Texture{
public:
     QColor textureColor;
     float smoothness=0.01; // 0-неровна 1-зеркало
};

class FigureEdge {
public:
QVector<QVector3D*> Points;
QVector3D Normal;
};
class FigurePolygon{
public:
QVector<QVector3D> Points;
};

class Figure
{   float upperRadius=0;
    float  lowerRadius=0;
    float height=0;
    int countAngle=6;
    QVector<FigurePolygon>  Polygons;
    QVector<FigureEdge> Edges;
public:
    Texture texture;
    QVector<QVector3D> Rotate={{1,0,0}, {0,1,0}, {0,0,1}};
    float Scale=1.0;
private:

    void makeEdges(QVector<QVector3D>& upperPolygon, QVector<QVector3D>& lowerPolygon);
    void makeCoppy(const Figure &figure);
    void addPolygonsToEdges(QVector<QVector3D>& Polygon);
public:
    void setSmoothness(float SmoothnessStep);
    void scaleGeometry(float scale);
    void makeApproximation(int accuracy);
    void makeApproximationRegion(int accuracy, float height, float accuracyHeight, float upperRadius, float lowerRadius);
    bool IsScale(float scale);
    void setNormals(MatrixAlgorithms*algoritms);
    Figure(float upperRadius, float  lowerRadius, float height, int countAngle);
    QVector<QVector3D> makePolygon( float radius  , float height   , int countAngle);
    void setFaces();
    QVector<FigurePolygon> & getPolygonsByRef();
    QVector<FigureEdge>& getEdgesByRef();
    QVector<FigurePolygon> & getPointsByRef();
    Figure(const Figure &figure);
    Figure& operator=(const Figure &figure);
    ~Figure();

};

#endif // FIGURE_H
