#include "screenshot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenShot* instance = ScreenShot::Instance();
    instance->show();


    return a.exec();
}
