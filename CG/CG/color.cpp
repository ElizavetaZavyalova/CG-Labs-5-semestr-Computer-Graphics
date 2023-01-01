#include "color.h"
#define MAXCANAL 255
#define MINCANAL 0


ColorAlgorithms::ColorAlgorithms()
{

}


QColor ColorAlgorithms::sumColor(QColor&color1, QColor&color2){
    int red=getCorrectCanal(color1.red()+color2.red());
    int green=getCorrectCanal(color1.green()+color2.green());
    int blue=getCorrectCanal(color1.blue()+color2.blue());
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::multiplyColor(QColor& color1, QColor& color2){
    int red=getCorrectCanal(color1.red()*color2.red());
    int green=getCorrectCanal(color1.green()*color2.green());
    int blue=getCorrectCanal(color1.blue()*color2.blue());
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::diffColor(QColor&color1, QColor&color2){
    int red=getCorrectCanal(color1.red()-color2.red());
    int green=getCorrectCanal(color1.green()-color2.green());
    int blue=getCorrectCanal(color1.blue()-color2.blue());
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::divColor(QColor&color1, QColor&color2){
    int red=getCorrectCanal(color1.red()/getCorrectCanal((color2.red()+1)));
    int green=getCorrectCanal(color1.green()/getCorrectCanal((color2.green()+1)));
    int blue=getCorrectCanal(color1.blue()/getCorrectCanal((color2.blue()+1)));
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::multiplyColorNumber(const QColor& color, const float number){
    int red=getCorrectCanal(((float)color.red())*number);
    int green=getCorrectCanal(((float)color.green())*number);
    int blue=getCorrectCanal(((float)color.blue())*number);
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::sumColorNumber(QColor& color,float number){
    number=getCorrectCanal(number);
    int red=getCorrectCanal(((float)color.red())+number);
    int green=getCorrectCanal(((float)color.green())+number);
    int blue=getCorrectCanal(((float)color.blue())+number);
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::diffColorNumber(QColor& color,float number){
    number=getCorrectCanal(number);
    int red=getCorrectCanal(((float)color.red())-number);
    int green=getCorrectCanal(((float)color.green())-number);
    int blue=getCorrectCanal(((float)color.blue())-number);
    return QColor(red, green, blue);
}
QColor ColorAlgorithms::divColorNumber(QColor& color,float number){
    number=getCorrectCanal(number+1);
    int red=getCorrectCanal(((float)color.red())/number);
    int green=getCorrectCanal(((float)color.green())/number);
    int blue=getCorrectCanal(((float)color.blue())/number);
    return QColor(red, green, blue);
}
int ColorAlgorithms::getCorrectCanal(float canal){
    if(canal<MINCANAL){
        return 0;
    }
    if(canal>MAXCANAL){
        return MAXCANAL;
    }
    return canal;
}
