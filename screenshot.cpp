#include "screenshot.h"
#include "ui_screenshot.h"


ScreenShot::ScreenShot()
{
    ui->setupUi(this);
    tray = new QSystemTrayIcon;
    icon.addFile(":/new/prefix1/C:/Users/Mercer/Desktop/1468956197_Screenshot.ico");
    tray->setIcon(icon);
    tray->setToolTip("Ready to shot");
    tray->show();
}

ScreenShot::~ScreenShot()
{
    delete ui;
}

void ScreenShot::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers()==Qt::AltModifier)
    {
        if(e->key()==Qt::Key_Alt)
        {
            Shot();
        }
    }

}

void ScreenShot::mousePressEvent(QMouseEvent *e)
{
    if(finish==true)
    {
        rubber = new  QRubberBand(QRubberBand::Rectangle,this);
        rubber->show();
        origin = e->pos();
        rubber->setGeometry(origin.x(),origin.y(),0,0);
        finish = false;
    }
}

void ScreenShot::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        end = e->pos();
        int w = abs(end.x()-origin.x());
        int h = abs(end.y()-origin.y());
        int x = origin.x()<end.x()?origin.x():end.x();
        int y = origin.y()<end.y()?origin.y():end.y();
        rubber->setGeometry(x,y,w,h);
        setLabel(w,h,x,y);
    }

}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e)
{

        if(e->button()==Qt::LeftButton)
        {
            end = e->pos();//记录终点坐标
            grabScreen();
        }
        else if(e->button()==Qt::RightButton)
        {
            finish = true;
            rubber->close();
            label->close();
        }


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

void ScreenShot::setLabel(int w,int h,int x,int y)
{
    QString size = QString("%1 x %2      ").arg(w).arg(h);
    label->setText(size);
    QRect rect(label->contentsRect());
    if(y>rect.height())
        label->move(QPoint(x,y-rect.height()));
    else
        label->move(QPoint(x,y));
    label->show();
}

void ScreenShot::creatActions()
{

}

void ScreenShot::creatMenu()
{

}

void ScreenShot::Shot()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect deskRect = desktop->screenGeometry();
    width = deskRect.width();
    height = deskRect.height();
    this->resize(width,height);
    this ->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    finish = true;
    setBackground(width,height);
    rubber =  NULL;
    origin = end = QPoint(0,0);
    label = new QLabel("");
    label->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->show();
}
