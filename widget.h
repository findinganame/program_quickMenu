#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSystemTrayIcon>
#include<QMenu>
#include<QDialog>
#include<QLabel>
#include<QHBoxLayout>
#include<QTimer>
#include<QMovie>
#include<QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initUI();
protected:
    //重写绘图事件，虚函数
    void paintEvent(QPaintEvent *);

private slots:
    void slot_trayIconActived(QSystemTrayIcon::ActivationReason reason);
    void on_btn_hide_clicked();

    void on_btn_band3_clicked();

    void on_btn_band40_clicked();
    void slot_timerout();

    void on_btn_self_clicked();

private:
    Ui::Widget *ui;
    int posx;
    int posy;
    QMenu* trayMenu;
    QAction* btnBand3;
    QAction* btnBand40;
    QAction* actSelf;
    QAction* actShow;
    QAction* actExit;
    QSystemTrayIcon* trayIcon;
    QDialog dlg;
    QLabel* l=new QLabel();
    QHBoxLayout *hLayout = new QHBoxLayout();
    QMovie* m;
    QTimer* timerDig;
    QProcess cmd;
};
#endif // WIDGET_H
