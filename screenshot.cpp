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
    switch(choice)
    {
    case 0:
        if(e->key()==Qt::Key_Escape)
        {
            this->hide();
        }
        break;
    case 1:
        if(e->key()==Qt::Key_Escape)
        {
            colorLabel->close();
            this->hide();
        }
    }


}


void ScreenShot::mousePressEvent(QMouseEvent *e) //鼠标按下
{
    switch(choice){
    case 0:
        if(shot==true)
        {
            rubber = new  QRubberBand(QRubberBand::Rectangle,this);
            rubber->show();
            origin = e->pos();
            rubber->setGeometry(origin.x(),origin.y(),0,0);
            shot = false;
        }
        else
        {
            rubber->close();
            label->close();
            done->close();
            rubber = new  QRubberBand(QRubberBand::Rectangle,this);
            rubber->show();
            origin = e->pos();
            rubber->setGeometry(origin.x(),origin.y(),0,0);
        }
        break;
    case 1:
//        QColorDialog *c;
//        c->setCurrentColor(color);
        break;
    case 2:
        break;
    }

}



void ScreenShot::mouseMoveEvent(QMouseEvent *e) //鼠标移动
{
    QPoint p = e->pos();
    QImage pic = bg;

    switch(choice){
    case 0:
        if(e->buttons() & Qt::LeftButton)
        {
            end = e->pos();
            pSize();
            rubber->setGeometry(px,py,pw,ph);
            setLabel(pw,ph,px,py);
            setButton(pw,ph,px,py);
        }
        break;
    case 1:

        color = pic.pixel(p.x(),p.y());
        colorLabel->setText(tr("R %1    G %2    B %3    ").arg(color.red())
                           .arg(color.green()).arg(color.blue()));

        colorLabel->move(QPoint(p.x() + 10,p.y() + 10));
        colorLabel->show();
        break;
    case 2:
          ;
    }


}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e) //鼠标松开
{

        if(e->button()==Qt::LeftButton)
        {

        }
        else if(e->button()==Qt::RightButton)
        {
            switch (choice) {
            case 0:
                shot = true;
                rubber->close();
                label->close();
                done->close();
                break;
            case 1:
                colorLabel->close();
                this->hide();
                break;
            }

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

void ScreenShot::setBackground(int w, int h,float n)
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
            r = qRed(bg.pixel(i,j))*n;
            g = qGreen(bg.pixel(i,j))*n;
            b = qBlue(bg.pixel(i,j))*n;
            bg_grey.setPixel(i,j,qRgb(r,g,b));
        }
    }
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(bg_grey));
    this->setPalette(palette);
    this->showFullScreen();
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
        case QSystemTrayIcon::Trigger: Shot(0.6);choice = 0;//choice为0为截屏
        break;
        default:break;
    }
}

void ScreenShot::Shot(float n)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect deskRect = desktop->screenGeometry();
    width = deskRect.width();
    height = deskRect.height();
    this->setMouseTracking(true);
    this->resize(width,height);
    this ->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    shot = reShot = true;
    setBackground(width,height,n);
    rubber =  NULL;
    origin = end = QPoint(0,0);
    label = new QLabel("");
    colorLabel = new QLabel("");

    done = new QPushButton("Done");

    label->setAttribute(Qt::WA_TranslucentBackground);
//    colorLabel->setAttribute(Qt::WA_TranslucentBackground);
    done->setAttribute(Qt::WA_TranslucentBackground);

    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    label->setPalette(pal);
//    colorLabel->setPalette(pal);
    done->setPalette(pal);

    label->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    colorLabel->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    done->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);


    connect(done,SIGNAL(clicked()),this,SLOT(grabScreen()));
    this->show();
}

void ScreenShot::pickColor()
{
    Shot(1);
    choice = 1; //choice为1为取色


}

void ScreenShot::makeGif()
{
    choice = 2; //choice为2为录gif
}
