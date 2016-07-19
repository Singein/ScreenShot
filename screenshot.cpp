#include "screenshot.h"
#include "ui_screenshot.h"

ScreenShot* ScreenShot::instance = 0;
ScreenShot::ScreenShot()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect deskRect = desktop->screenGeometry();
    width = deskRect.width();
    height = deskRect.height();
    this->resize(width,height);
    this ->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    setBackground(width,height);

}

ScreenShot::~ScreenShot()
{
    delete ui;
}

void ScreenShot::keyPressEvent(QKeyEvent *e)
{

}

void ScreenShot::mousePressEvent(QMouseEvent *e)
{

}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e)
{

}

void ScreenShot::mouseMoveEvent(QMouseEvent *e)
{

}

void ScreenShot::grabScreen()
{

}

void ScreenShot::setBackground(int w, int h)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("bg.bmp","bmp");
}

void ScreenShot::setLabel()
{

}

void ScreenShot::show()
{
    QWidget::show();
    setBackground(width,height);
}
