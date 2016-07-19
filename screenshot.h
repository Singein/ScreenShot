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
#include <QSystemTrayIcon>
#include <QKeyEvent>
#include <QMenu>
#include <QDir>
#include <QDateTime>

namespace Ui {
class ScreenShot;
}

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    ~ScreenShot();
    ScreenShot();
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);
    void setBackground(int w,int h);
    void grabScreen();
    void setLabel(int w,int h,int x,int y);


private:
    Ui::ScreenShot *ui;
    QRubberBand *rubber;
    QIcon icon;
    QPoint origin;//鼠标起始位置
    QPoint end;//鼠标结束位置
    QImage bg;//存贮当前桌面截图
    QLabel *label;//用来框选图片
    int width;//屏幕宽度
    int height;//屏幕高度
    int pw,ph,px,py;
    static ScreenShot* instance;
    bool finish;

    QSystemTrayIcon* tray;
    QAction *quitAction;               //退出事件
    QAction *aboutAction;                //设置事件
    QMenu *trayIconMenu;               //托盘图标点击菜单

    void creatActions();
    void creatMenu();
    void pSize();
public slots:
    void Shot();
    void iconActivied(QSystemTrayIcon::ActivationReason reason);

};

#endif // SCREENSHOT_H
