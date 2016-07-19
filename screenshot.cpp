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
    rubber =  NULL;
    origin = end = QPoint(0,0);
    label = new QLabel("");
    label->setWindowFlags(Qt::FramelessWindowHint);


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
//    screen->grabWindow(0).save("bg.bmp","bmp");

    int r,g,b;
    bg = screen->grabWindow(0).toImage();
    QImage bg_grey(w,h,QImage::Format_RGB32);
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            r = qRed(bg.pixel(i,j))*0.5;
            g = qGreen(bg.pixel(i,j))*0.5;
            b = qBlue(bg.pixel(i,j))*0.5;
            bg_grey.setPixel(i,j,qRgb(r,g,b));
        }
    }
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(bg_grey));
    this->setPalette(palette);
}

void ScreenShot::setLabel()
{

}

void ScreenShot::show()
{
    QWidget::show();
    setBackground(width,height);
}
