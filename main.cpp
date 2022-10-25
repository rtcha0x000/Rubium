#include "rubium.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    QApplication a(argc, argv);
    QPixmap pix(":/new/prefix1/alexander-ant-Lm130MBkAeI-unsplash.jpg");
    QSplashScreen splash(pix);
    splash.show();
    a.processEvents();
    Rubium w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
