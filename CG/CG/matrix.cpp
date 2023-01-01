#include "matrix.h"
#include <qmath.h>
MatrixAlgorithms::MatrixAlgorithms()
{

}
QPoint MatrixAlgorithms::Proection(const QVector3D& Point, int key){
    switch(key){
    {
        case _X:
            return(QPoint(Point.y(), Point.z()));
        case X:
            return(QPoint(-Point.y(), -Point.z()));
        case _Y:
             return(QPoint(Point.x(), Point.z()));
        case Y:
             return(QPoint(-Point.x(), -Point.z()));
        case _Z:
            return(QPoint(Point.x(), Point.y()));
        case Z:
             return(QPoint(-Point.x(), -Point.y()));
    }
    };
    return IsometryProection(Point);

}
QPoint MatrixAlgorithms::IsometryProection(const QVector3D& Point){
    /*float z=1-Point.y();
    return QPoint(Point.x()/z,Point.z()/z);*/
    float y=1-Point.y();
    return QPoint((Point.x()-Point.y())/sqrt(2),
                      (Point.x() + 2*Point.z() + Point.y()) / sqrt(6));
}
float MatrixAlgorithms::ModVector(const QVector3D& vector){
    return qSqrt(vector.x()*vector.x() +\
                 vector.y()*vector.y() +\
                 vector.z()*vector.z());
}
float MatrixAlgorithms::cosVector(const QVector3D& cameraView,const QVector3D& normal){
    return (float)(cameraView.x()*normal.x()+\
            cameraView.y()*normal.y()+\
            cameraView.z()*normal.z())/\
            (float)(ModVector(cameraView)*ModVector(normal));
}
QVector3D  MatrixAlgorithms::getVectorProduct(const QVector3D& Point1, const QVector3D& Point2){
    return QVector3D((Point1.y()*Point2.z()-Point2.y()*Point1.z()),\
                    -(Point1.x()*Point2.z()-Point2.x()*Point1.z()),\
                     (Point1.x()*Point2.y()-Point2.x()*Point1.y()));
}
bool MatrixAlgorithms::IsVisible(const QVector3D& cameraView, const QVector3D& Normal){
    if(cosVector(cameraView,Normal)<0){
        return true;
    }
     return false;
}
QVector3D  MatrixAlgorithms::getNormalVector(const QVector3D& Point1, const QVector3D& Point2, const QVector3D& Point3){
    QVector3D vector1(Point2.x()-Point1.x(),  Point2.y()-Point1.y(),  Point2.z()-Point1.z());
    QVector3D vector2(Point3.x()-Point1.x(),  Point3.y()-Point1.y(),  Point3.z()-Point1.z());
    QVector3D normalVector = getVectorProduct(vector1,vector2);
    normalVector = makeEVector(normalVector);
    if(cosVector(Point1,normalVector)<0){
        return QVector3D(-normalVector.x(),-normalVector.y(), -normalVector.z());
    }
    return normalVector;
}

QVector3D MatrixAlgorithms::makeEVector(const QVector3D& vector){
    float mod =  ModVector(vector);
    if(mod==0){
        return vector;
    }
    return  QVector3D(vector.x()/mod,\
                      vector.y()/mod,\
                      vector.z()/mod);

}
QVector3D MatrixAlgorithms::changeBasis(const QVector3D&Point, const QVector<QVector3D>& vector){
    return QVector3D(vector[0].x()*Point.x()   +  vector[0].y()*Point.y()   +  vector[0].z()*Point.z(),
                     vector[1].x()*Point.x()   +  vector[1].y()*Point.y()   +  vector[1].z()*Point.z(),
                     vector[2].x()*Point.x()   +  vector[2].y()*Point.y()   +  vector[2].z()*Point.z());
}

QVector2D MatrixAlgorithms::Rotate(const QVector2D& Point,const  float angle){
    float cosAngle = qCos(qDegreesToRadians(angle));
    float sinAngle = qSin(qDegreesToRadians(angle));
    return QVector2D(Point.x()*cosAngle    +  Point.y()*(-sinAngle),\
                     Point.x()*sinAngle    +  Point.y()*cosAngle);
}
QVector3D MatrixAlgorithms::Scale(const QVector3D& Point,const float scale=1){
    return QVector3D(Point.x()*scale,\
                     Point.y()*scale,\
                     Point.z()*scale);
}

QVector3D MatrixAlgorithms::RotateX(const QVector3D& Point, const float angle){
    float cosAngle = qCos(qDegreesToRadians(angle));
    float sinAngle = qSin(qDegreesToRadians(angle));
    return QVector3D(Point.x()*1    +  Point.y()*0         +  Point.z()*0, \
                     Point.x()*0    +  Point.y()*cosAngle  +  Point.z()*(-sinAngle), \
                     Point.x()*0    +  Point.y()*sinAngle  +  Point.z()* cosAngle);
}
QVector3D MatrixAlgorithms::GetMedianVector(const QVector3D&cameraView, const QVector3D&lightView){
    QVector3D MedianVector=sumVector(cameraView,lightView);
    return this->makeEVector(MedianVector);

}
QVector3D MatrixAlgorithms::diffVector(const QVector3D&reducedVector,const QVector3D& deductibleVector){
    return QVector3D(reducedVector.x()-deductibleVector.x(),\
                     reducedVector.y()-deductibleVector.y(),\
                     reducedVector.z()-deductibleVector.z());
}
QVector3D MatrixAlgorithms::sumVector(const QVector3D&vector1, const QVector3D& vector2){
    return QVector3D(vector1.x()+vector2.x(),\
                     vector1.y()+vector2.y(),\
                     vector1.z()+vector1.z());
}
QVector3D MatrixAlgorithms::RotateY(const QVector3D& Point,const  float angle){
    float cosAngle = qCos(qDegreesToRadians(angle));
    float sinAngle = qSin(qDegreesToRadians(angle));
    return QVector3D(Point.x()*cosAngle     +   Point.y()*0   +   Point.z()*sinAngle, \
                     Point.x()*0            +   Point.y()*1   +   Point.z()*0, \
                     Point.x()*(-sinAngle)  +   Point.y()*0   +   Point.z()*cosAngle);
}
QVector3D MatrixAlgorithms::RotateZ(const QVector3D& Point, const float angle){
    float cosAngle = qCos(qDegreesToRadians(angle));
    float sinAngle = qSin(qDegreesToRadians(angle));
    return QVector3D(Point.x()*cosAngle  +   Point.y()*(-sinAngle)  +  Point.z()*0, \
                     Point.x()*sinAngle  +   Point.y()*cosAngle     +  Point.z()*0, \
                     Point.x()*0         +   Point.y()*0            +  Point.z()*1);
}

QVector3D MatrixAlgorithms::RotateVector(const QVector3D& Point, const QVector3D&EVector,  const float angle){
    float cosAngle = qCos(qDegreesToRadians(angle));
    float sinAngle = qSin(qDegreesToRadians(angle));
    return QVector3D(                   (cosAngle  +  (1 - cosAngle)*pow(EVector.x(),2))                  *Point.x()+\
                       ((1 - cosAngle)*EVector.x()*EVector.y()  -  sinAngle*EVector.z())                  *Point.y()+\
                       ((1 - cosAngle)*EVector.x()*EVector.z()  +  sinAngle*EVector.y())                  *Point.z(),

                       ((1 - cosAngle)*EVector.x()*EVector.y()  +  sinAngle*EVector.z())                  *Point.x()+\
                                                     (cosAngle  +  (1 - cosAngle)*pow(EVector.y(),2))     *Point.y()+\
                       ((1 - cosAngle)*EVector.y()*EVector.z()  -  sinAngle*EVector.x())                  *Point.z(),\

                       ((1 - cosAngle)*EVector.x()*EVector.z()  -  sinAngle*EVector.y())                  *Point.x()+\
                       ((1 - cosAngle)*EVector.y()*EVector.z()  +  sinAngle*EVector.x())                  *Point.y()+\
                                                    (cosAngle   +  (1 - cosAngle)*pow(EVector.z(),2))     *Point.z());
}
