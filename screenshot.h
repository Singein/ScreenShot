#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QRubberBand>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QScreen>

namespace Ui {
class ScreenShot;
}

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    ~ScreenShot();
    static ScreenShot *Instance()
    {
        if(!instance)
            instance = new ScreenShot();

        return instance;
    }


    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

    void setBackground(int w,int h);
    void grabScreen();
    void setLabel();

    void show();

private:
    Ui::ScreenShot *ui;
    QRubberBand *rubber;
    QPoint origin;//鼠标起始位置
    QPoint end;//鼠标结束位置
    QImage c_shot;//存贮当前桌面截图
    QLabel label;//用来框选图片
    int width;//屏幕宽度
    int height;//屏幕高度
    static ScreenShot* instance;
    ScreenShot();

};

#endif // SCREENSHOT_H
