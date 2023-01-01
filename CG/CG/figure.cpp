#include "figure.h"
#define UPPER 0
#define LOWER Polygons.size()-1
#define MinScale 0.1
#define MaxScale 3
#define MinSmoothness 0
#define MaxSmoothness 1
void Figure::setNormals(MatrixAlgorithms*algoritms){
    for(int normal=0; normal<this->Edges.size(); normal++){
        Edges[normal].Normal=algoritms->getNormalVector(*Edges[normal].Points[0],\
                                           *Edges[normal].Points[1],*Edges[normal].Points[2]);
        if(*Edges[normal].Points[0]==*Edges[normal].Points[1]){
            Edges[normal].Normal=algoritms->getNormalVector(*Edges[normal].Points[1],\
                                               *Edges[normal].Points[2],*Edges[normal].Points[3]);
        }
    }
}

void Figure::setSmoothness(float SmoothnessStep){
    if(texture.smoothness+SmoothnessStep>MinSmoothness&&texture.smoothness+SmoothnessStep<MaxSmoothness){
        texture.smoothness+=SmoothnessStep;
    }
}
Figure::Figure(float upperRadius, float lowerRadius, float height, int countAngle){
    this->countAngle=countAngle;
    this->lowerRadius=lowerRadius;
    this->upperRadius=upperRadius;
    this->height=height;
    this->setFaces();
    this->texture.textureColor=QColor(0,0,255);
}
void Figure::scaleGeometry(float scale){
    this->lowerRadius*=scale;
    this->upperRadius*=scale;
    this->height*=scale;
}
void Figure::makeApproximationRegion(int accuracy, float height, float accuracyHeight, float upperRadius, float lowerRadius){
    int polygonsSize=LOWER+1;
    FigurePolygon polygon;
    //float accuracyHeight=height*0.5;
    int directionAccuracyRadiusStep=(upperRadius<lowerRadius)?(1):(-1);
    float accuracyRadius=upperRadius;
    polygon.Points=makePolygon(accuracyRadius, accuracyHeight, countAngle+accuracy-1);
    this->Polygons.append(polygon);
    float accuracyHeightStep=height/accuracy;
    float  accuracyRadiusStep=directionAccuracyRadiusStep*(lowerRadius-upperRadius)/accuracy;
    for(int polygonNumber=0+polygonsSize; polygonNumber<accuracy+polygonsSize; polygonNumber++){
        accuracyHeight-=accuracyHeightStep;
        accuracyRadius+=(float)(directionAccuracyRadiusStep)*accuracyRadiusStep;
        polygon.Points=makePolygon(accuracyRadius, accuracyHeight, countAngle+accuracy-1);
        this->Polygons.append(polygon);
        this->makeEdges(Polygons[polygonNumber].Points, Polygons[polygonNumber+1].Points);
    }

}
void Figure::makeApproximation(int accuracy){
    this->Polygons.clear();
    this->Edges.clear();
    float zeroAccuray= 0.0;
    if(accuracy>1){
    makeApproximationRegion(accuracy, zeroAccuray, 0.5*height,zeroAccuray, upperRadius);
    }
    makeApproximationRegion(accuracy, height, 0.5*height, upperRadius, lowerRadius);
   if(accuracy>1){
   makeApproximationRegion(accuracy, zeroAccuray, -0.5*height,  lowerRadius,zeroAccuray);
   }
    addPolygonsToEdges(Polygons[UPPER].Points);
    addPolygonsToEdges(Polygons[LOWER].Points);
}

bool Figure::IsScale(float scale){
    if(this->Scale*scale>=MinScale&&this->Scale*scale<=MaxScale){
        return true;
    }
    return false;
}

Figure::~Figure(){

}
void Figure::addPolygonsToEdges(QVector<QVector3D>& Polygon){
    FigureEdge edge;
    for(int point=0; point<Polygon.size(); point++){
        edge.Points.append(&Polygon[point]);
    }
    Edges.append(edge);
}
QVector<QVector3D> Figure::makePolygon(float radius, float height, int countAngle){

    QVector<QVector3D> Polygon;
    for(int count=0;  count<countAngle; count++){
         int angle=(360*count)/countAngle;
        float cosAngle = qCos(qDegreesToRadians(angle));
        float sinAngle = qSin(qDegreesToRadians(angle));
        Polygon.append(QVector3D(radius*cosAngle, radius*sinAngle, height));

    }
    return  Polygon;

}
void Figure::makeEdges(QVector<QVector3D>& upperPolygon, QVector<QVector3D>& lowerPolygon){
    int pointsSize=upperPolygon.size();
    for(int point=0; point<pointsSize; point++){
        FigureEdge edge;
        edge.Points.append(&upperPolygon[point]);
        edge.Points.append(&upperPolygon[(point + 1)%pointsSize]);
        edge.Points.append(&lowerPolygon[(point + 1)%pointsSize]);
        edge.Points.append(&lowerPolygon[point]);
        Edges.append(edge);
    }

}

void Figure::setFaces(){
    this->Polygons.clear();
    FigurePolygon polygon;
    polygon.Points=makePolygon(upperRadius, (height*0.5), countAngle);
    this->Polygons.append(polygon);
    polygon.Points=makePolygon(lowerRadius, -(height*0.5), countAngle);
    this->Polygons.append(polygon);
    this->makeEdges(Polygons[UPPER].Points, Polygons[LOWER].Points);
    this->addPolygonsToEdges(Polygons[UPPER].Points);
    this->addPolygonsToEdges(Polygons[LOWER].Points);
}

QVector<FigurePolygon>& Figure::getPolygonsByRef(){
    return this->Polygons;
}
QVector<FigureEdge>& Figure::getEdgesByRef(){
    return this->Edges;
}
QVector<FigurePolygon>& Figure::getPointsByRef(){
    return getPolygonsByRef();
}
void Figure::makeCoppy(const Figure &figure){
    this->Polygons=figure.Polygons;

    for(int polygonNumber=0; polygonNumber<Polygons.size()-1; polygonNumber++){
        this->makeEdges(Polygons[polygonNumber].Points,Polygons[polygonNumber+1].Points);
    }
    this->addPolygonsToEdges(Polygons[UPPER].Points);
    this->addPolygonsToEdges(Polygons[LOWER].Points);
    for(int normal=0; normal<=this->Edges.size(); normal++){
        this->Edges[normal].Normal=figure.Edges[normal].Normal;
    }
    this->upperRadius=figure.lowerRadius;
    this->lowerRadius=figure.upperRadius;
    this->height=figure.height;
    this->countAngle=figure.countAngle;
    this->Rotate=figure.Rotate;
    this->Scale=figure.Scale;
    this->texture=figure.texture;
}
Figure::Figure(const Figure &figure){
    this->makeCoppy(figure);
}
Figure& Figure::operator=(const Figure &figure){
     this->makeCoppy(figure);
      return *this;
}
