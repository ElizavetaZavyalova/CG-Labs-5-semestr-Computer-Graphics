#include "shaders.h"


Shaders::Shaders(MatrixAlgorithms*matrix)
{
this->matrix=matrix;
this->color=new ColorAlgorithms;
}


Shaders::~Shaders(){
    delete color;
}
QColor Shaders::makeColor(const FigureEdge&edge, const Texture&texture, QVector3D &cameraPosition){
      QColor base=color->multiplyColorNumber(texture.textureColor,this->Intancity);

      QVector3D edgeDistance=makeItemDistance(edge);
      QVector3D lampDistance=matrix->diffVector(lamp->cordinates,edgeDistance);
      float cosNL= qMax(matrix->cosVector(edge.Normal,lampDistance),0.0);
      QColor lightColor=color->multiplyColorNumber(texture.textureColor,cosNL);
      lightColor=color->multiplyColorNumber(lightColor,lamp->getIntensity());

      QColor resault=color->sumColor(base,  lightColor);

      QVector3D cameraDistance=matrix->diffVector(edgeDistance, cameraPosition);
      QVector3D Ln=matrix->Scale(edge.Normal,cosNL);
      QVector3D Lp=matrix->diffVector(lampDistance,Ln);
      QVector3D R=matrix->diffVector(Ln, Lp);
      float cosRV=qMax(matrix->cosVector(R,cameraDistance),0.0);
      float specularCos=powf(cosRV,1.0/texture.smoothness);
      QColor specularColor=color->multiplyColorNumber(lamp->colorGlare,specularCos);
      specularColor=color->multiplyColorNumber(specularColor,lamp->getIntensity());
      return color->sumColor(resault,  specularColor);
}

void Shaders::setIntensity(float intensityStep){
    lamp->setIntensity(intensityStep);
}
void  Shaders::setSinIntensity(){
    lamp->changeIntensity();
}
QVector3D Shaders::makeItemDistance(const FigureEdge&edge){
    if(edge.Points.size()>4){
        return QVector3D(0,0,(*edge.Points[0]).z());
    }
    QVector3D edgeDistance={0,0,0};
    for(int point=0;point<edge.Points.size();point++){
        edgeDistance=matrix->sumVector(edgeDistance,*edge.Points[point]);
    }
    float scale=1.0/((float)edge.Points.size());
    return matrix->Scale(edgeDistance,scale);

}
void Shaders::setLamp(Lamp*lamp){
    this->lamp=lamp;
}
