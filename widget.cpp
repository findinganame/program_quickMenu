#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include<QPainter>
#include<QMessageBox>
#include<QRandomGenerator>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    dlg.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    dlg.setAttribute(Qt::WA_TranslucentBackground);
    hLayout->addWidget(l);
    dlg.setLayout(hLayout);
    timerDig = new QTimer(this);
    timerDig->setInterval(5000);
    connect(timerDig,&QTimer::timeout,this,&Widget::slot_timerout);
    initUI();
}

Widget::~Widget()
{
    delete ui;
}
//画背景图
void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(0, 0, width(), height(), QPixmap(":/ico/attachments/background.png"));
}


void Widget::initUI(){
    //初始化系统托盘
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    trayMenu=new QMenu(this);
    actShow=new QAction("显示窗口",this);
    actExit=new QAction("退出",this);
    btnBand3=new QAction("计算器",this);
    btnBand40=new QAction("无聊了",this);
    actSelf=new QAction("自定义",this);
    trayMenu->addAction(btnBand40);
    trayMenu->addAction(btnBand3);
    trayMenu->addAction(actSelf);
    trayMenu->addSeparator();
    trayMenu->addAction(actShow);
    trayMenu->addAction(actExit);
    connect(actShow,&QAction::triggered,this,[=](){
        this->show();
        this->move(posx,posy);
    });
    connect(actExit,&QAction::triggered,this,[=](){QApplication::exit(0);});
    connect(btnBand3,&QAction::triggered,this,[=](){on_btn_band3_clicked();});
    connect(btnBand40,&QAction::triggered,this,[=](){on_btn_band40_clicked();});
    connect(actSelf,&QAction::triggered,this,[=](){on_btn_self_clicked();});
    trayIcon=new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(QIcon(":/ico/attachments/ico_capoo.ico"));
    trayIcon->setToolTip("瓜瓜的快捷菜单");
    trayIcon->show();
    connect(trayIcon,&QSystemTrayIcon::activated,this,&Widget::slot_trayIconActived);
    QRect trayRect=trayIcon->geometry();
    int x,y,width,height;
    trayRect.getRect(&x,&y,&width,&height);
    posx=x-60;
    posy=y-this->height()-20;
    this->move(posx,posy);

}

void Widget::slot_trayIconActived(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
    case QSystemTrayIcon::Trigger:
        Widget::on_btn_band40_clicked();
        break;
    case QSystemTrayIcon::MiddleClick:
        Widget::on_btn_band40_clicked();
        break;
    default:
        break;
    }
}




void Widget::on_btn_hide_clicked()
{
    this->hide();
}


void Widget::on_btn_band3_clicked()
{
    cmd.start("calc");

}


void Widget::on_btn_band40_clicked()
{
    m=new QMovie(QString("attachments/%1.gif").arg(QRandomGenerator::global()->bounded(0,50)));
    QPixmap p=m->currentPixmap();
    dlg.setFixedSize(p.width(),p.height());

    l->setMovie(m);
    m->start();
    l->setScaledContents(true);

    dlg.show();
    timerDig->start();

}

void Widget::slot_timerout()
{
    dlg.hide();
    m->stop();
    delete m;
    m=nullptr;
    timerDig->stop();

}


void Widget::on_btn_self_clicked()
{
    QMessageBox::information(this,"自定义功能","请联系瓜瓜定制其他功能\n瓜瓜的QQ：1769992763\n加QQ请添加备注");
}

