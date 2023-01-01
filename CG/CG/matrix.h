#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>
#include <QVector3D>

class MatrixAlgorithms{
     enum proection{_X='1',X='2',_Y='3',Y='4',_Z='5',Z='6'};
public:
   QPoint Proection(const QVector3D& Point, const int key);
   QVector3D changeBasis(const QVector3D&Point, const QVector<QVector3D>& vector);
   QPoint IsometryProection(const QVector3D& Point);
   bool IsVisible(const QVector3D& cameraView, const QVector3D& Normal);
   QVector3D diffVector(const QVector3D&reducedVector,const QVector3D& deductibleVector);
   QVector3D sumVector(const QVector3D&vector1,const QVector3D& vector2);
   QVector3D GetMedianVector(const QVector3D&cameraView,const QVector3D&lightView);
   QVector3D getNormalVector(const QVector3D& Point1, const QVector3D& Point2,const QVector3D& Point3);
   QVector3D getVectorProduct(const QVector3D& Point1,const QVector3D& Point2);
   float ModVector(const QVector3D& vector);
   float cosVector(const QVector3D& cameraView,const QVector3D& Normal);
   QVector2D Rotate(const QVector2D& Point,const  float angle);
   QVector3D makeEVector(const QVector3D& vector);
   QVector3D Scale  (const QVector3D& Point, const float scale);
   QVector3D RotateX(const QVector3D& Point,const float   angle);
   QVector3D RotateY(const QVector3D& Point, const float   angle);
   QVector3D RotateZ(const QVector3D& Point,const float   angle);
   void changeBasisRotateVector(const QVector3D& vector, const float angle);
   QVector3D RotateVector(const QVector3D& Point,const QVector3D& vector,const float angle);
   MatrixAlgorithms();
};

#endif // MATRIX_H
