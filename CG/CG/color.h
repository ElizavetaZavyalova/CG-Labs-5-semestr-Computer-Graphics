#ifndef COLOR_H
#define COLOR_H
#include <QColor>

class ColorAlgorithms
{
public:
    ColorAlgorithms();
    int getCorrectCanal(float canal);
public:
    QColor sumColor(QColor&color1, QColor&color2);
    QColor multiplyColor(QColor& color1, QColor& color2);
    QColor diffColor(QColor&color1, QColor&color2);
    QColor divColor(QColor&color1, QColor&color2);
public:
    QColor sumColorNumber(QColor& color,float number);
    QColor diffColorNumber(QColor& color,float number);
    QColor divColorNumber(QColor& color,float number);
    QColor multiplyColorNumber(const QColor& color,const float number);

};

#endif // COLOR_H
