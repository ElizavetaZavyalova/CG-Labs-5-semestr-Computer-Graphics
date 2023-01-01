#include "engine.h"
#define MAXAPPROXIMATION 100
#define MINAPPROXIMATION 1

Engine::Engine(Figure*figure, Camera*camera, Lamp*lamp)
{

    this->setFigure(figure);
    this->setCamera(camera);

    this->matrix=new MatrixAlgorithms();
    this->shaders=new Shaders(matrix);
    this->setLamp(lamp);
    figure->setNormals(matrix);

}
void  Engine::setSinIntensity(){
    shaders->setSinIntensity();
}
void Engine::setIntensity(float intensityStep){
    shaders->setIntensity(intensityStep);
}
void Engine::setSmoothness(float SmoothnessStep){
    figure->setSmoothness(SmoothnessStep);
}
QColor Engine::makeColor(FigureEdge&edge){
      QVector3D camerPosition=camera->getCameraPosition();
      return shaders->makeColor(edge,figure->texture,camerPosition);
}
void Engine::setCameraNormal(int proectionNumber){
    camera->setNormal(proectionNumber);
}
int  Engine::getApproximation(){
    return this->approximation;
}
void Engine::setFigure(Figure*figure){
    this->figure=figure;
}
void Engine::setCamera(Camera*camera){
    this->camera=camera;
}
void Engine::setLamp(Lamp*lamp){
    this->shaders->setLamp(lamp);
}
Engine::~Engine(){
    delete matrix;
    delete shaders;
}
QPoint Engine::Proection(QVector3D& Point,int proectionNumber ){
    return matrix->Proection(Point, proectionNumber);
}
bool Engine::IsDraw(QVector3D& cameraView, QVector3D& Normal){
    return matrix->IsVisible(cameraView,Normal);
}

QVector3D Engine::makeRotateEVector(QVector2D& vector){
    QVector2D perpendicularVector=matrix->Rotate(vector, 90);
    QVector3D perpendicular3DVector(perpendicularVector.x(), perpendicularVector.y(), 0);
    return matrix->makeEVector(perpendicular3DVector);

}
void Engine::makeApproximation(int accuracy){
     if(approximation+accuracy<MINAPPROXIMATION||approximation+accuracy>MAXAPPROXIMATION){
         return;
     }
     approximation+=accuracy;
     figure->makeApproximation(approximation);
     figure->setNormals(matrix);
     float scale=figure->Scale;
     figure->Scale=1;
     Scale(scale);
    // changeFigureBasis(figure->Rotate);

}
void Engine::makeScale(float   scale){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->Scale(polygon[edge].Points[point],scale);
        }
    }
}
void Engine::scaleGeometry(float   scale){
    makeScale(scale);
    figure->scaleGeometry(scale);

}
void Engine::Scale (float scale){
    if(!figure->IsScale(scale)){
        return;
    }
    makeScale(scale);
    figure->Scale*=scale;
}
void Engine::RotateX(float angle){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->RotateX(polygon[edge].Points[point],angle);
        }
    }
    QVector<FigureEdge> &edges=figure->getEdgesByRef();
    for(int edge=0; edge<edges.size(); edge++){
         edges[edge].Normal=matrix->RotateX(edges[edge].Normal,angle);
    }
    for(int vectorNumber=0; vectorNumber<figure->Rotate.size(); vectorNumber++){
    figure->Rotate[vectorNumber]=matrix->RotateX(figure->Rotate[vectorNumber], angle);
    }

}
void Engine::changeFigureBasis(QVector<QVector3D>& vector){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->changeBasis(polygon[edge].Points[point], vector);
        }
    }
    QVector<FigureEdge> &edges=figure->getEdgesByRef();
    for(int edge=0; edge<edges.size(); edge++){
         edges[edge].Normal=matrix->changeBasis(edges[edge].Normal,vector);
    }
}
void  Engine::changeBasis(QVector<QVector3D>& vector){
    changeFigureBasis(vector);
    for(int vectorNumber=0; vectorNumber<figure->Rotate.size(); vectorNumber++){
    figure->Rotate[vectorNumber]=matrix->changeBasis(figure->Rotate[vectorNumber], vector);
    }
}
void Engine::RotateY(float angle){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->RotateY(polygon[edge].Points[point],angle);
        }
    }
    QVector<FigureEdge> &edges=figure->getEdgesByRef();
    for(int edge=0; edge<edges.size(); edge++){
         edges[edge].Normal=matrix->RotateY(edges[edge].Normal,angle);
    }
    for(int vectorNumber=0; vectorNumber<figure->Rotate.size(); vectorNumber++){
    figure->Rotate[vectorNumber]=matrix->RotateY(figure->Rotate[vectorNumber], angle);
    }
}
void Engine::RotateZ(float angle){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->RotateZ(polygon[edge].Points[point],angle);
        }
    }
    QVector<FigureEdge> &edges=figure->getEdgesByRef();
    for(int edge=0; edge<edges.size(); edge++){
         edges[edge].Normal=matrix->RotateZ(edges[edge].Normal,angle);
    }
    for(int vectorNumber=0; vectorNumber<figure->Rotate.size(); vectorNumber++){
    figure->Rotate[vectorNumber]=matrix->RotateZ(figure->Rotate[vectorNumber], angle);
    }

}
void Engine::RotateVector(QVector3D& vector, float angle){
    QVector<FigurePolygon> &polygon=figure->getPolygonsByRef();
    for(int edge=0; edge<polygon.size(); edge++){
        for(int point=0; point<polygon[edge].Points.size(); point++){
            polygon[edge].Points[point]=matrix->RotateVector(polygon[edge].Points[point],vector, angle);
        }
    }
    QVector<FigureEdge> &edges=figure->getEdgesByRef();
    for(int edge=0; edge<edges.size(); edge++){
           edges[edge].Normal=matrix->RotateVector(edges[edge].Normal, vector, angle);
    }
    for(int vectorNumber=0; vectorNumber<figure->Rotate.size(); vectorNumber++){
    figure->Rotate[vectorNumber]=matrix->RotateVector(figure->Rotate[vectorNumber], vector, angle);
    }
}




