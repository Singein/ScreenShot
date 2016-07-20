#include "screenshot.h"
#include "ui_screenshot.h"
#include <QMessageBox>

ScreenShot::ScreenShot()
{
    ui->setupUi(this);
    tray = new QSystemTrayIcon;
    icon.addFile(":/new/prefix1/C:/Users/Mercer/Desktop/1468956197_Screenshot.ico");    
    tray->setIcon(icon);
    tray->show();
    creatActions();
    creatMenu();
    connect(tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(iconActivied(QSystemTrayIcon::ActivationReason)));
}

ScreenShot::~ScreenShot()
{
    delete ui;
}

void ScreenShot::pSize()
{
    pw = abs(end.x()-origin.x());
    ph = abs(end.y()-origin.y());
    px = origin.x()<end.x()?origin.x():end.x();
    py = origin.y()<end.y()?origin.y():end.y();
}

void ScreenShot::closeEvent(QCloseEvent *e)
{
    e->ignore();
    this->hide();
}

void ScreenShot::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {
        this->hide();
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
        pSize();
        rubber->setGeometry(px,py,pw,ph);
        setLabel(pw,ph,px,py);
        setButton(pw,ph,px,py);
    }
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e)
{

        if(e->button()==Qt::LeftButton)
        {
            end = e->pos();//记录终点坐标  
        }
        else if(e->button()==Qt::RightButton)
        {
            finish = true;
            rubber->close();
            label->close();
            done->close();
        }
}

void ScreenShot::grabScreen()
{
    QImage pic = bg.copy(px,py,pw,ph);
    QString path = QDir::currentPath()+"/"+QDateTime::currentDateTime().toString("yymmddhhmmss")+".jpg";
    pic.save(path);
    QDesktopServices::openUrl(QUrl(path));
    QClipboard *b = QApplication::clipboard();
    b->setImage(pic);
    done->close();
    label->close();
    rubber->close();
    this->hide();

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
            r = qRed(bg.pixel(i,j))*0.6;
            g = qGreen(bg.pixel(i,j))*0.6;
            b = qBlue(bg.pixel(i,j))*0.6;
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

void ScreenShot::setButton(int w,int h,int x,int y)
{
    QRect rect(done->contentsRect());
    done->move(QPoint(x+w-rect.width(),y+h-rect.height()));
    done->show();
}

void ScreenShot::creatActions()
{
    quitAction = new QAction("Quit",this);
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    pickAction = new QAction("pick color",this);
    connect(pickAction,SIGNAL(triggered()),this,SLOT(pickColor()));
    gifAction = new QAction("make gif",this);
    connect(gifAction,SIGNAL(triggered()),this,SLOT(makeGif()));
}

void ScreenShot::creatMenu()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(pickAction);
    trayIconMenu->addAction(gifAction);
    trayIconMenu->addAction(quitAction);
    tray->setContextMenu(trayIconMenu);
}

void ScreenShot::iconActivied(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger: Shot();break;
        default:break;
    }
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
    done = new QPushButton("Done");
    label->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    done->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    connect(done,SIGNAL(clicked()),this,SLOT(grabScreen()));
    this->show();
}

void ScreenShot::pickColor()
{

}

void ScreenShot::makeGif()
{

}
