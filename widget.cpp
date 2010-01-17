#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pic = new Picture(this);

    connect(ui->translateXSlider, SIGNAL(valueChanged(int)), pic, SLOT(setTranslateX(int)));
    connect(ui->translateYSlider, SIGNAL(valueChanged(int)), pic, SLOT(setTranslateY(int)));
    connect(ui->translateZSlider, SIGNAL(valueChanged(int)), pic, SLOT(setTranslateZ(int)));

    connect(ui->rotateXSlider, SIGNAL(valueChanged(int)), pic, SLOT(setRotateX(int)));
    connect(ui->rotateYSlider, SIGNAL(valueChanged(int)), pic, SLOT(setRotateY(int)));
    connect(ui->rotateZSlider, SIGNAL(valueChanged(int)), pic, SLOT(setRotateZ(int)));

    connect(ui->scaleXSlider, SIGNAL(valueChanged(int)), pic, SLOT(setScaleX(int)));
    connect(ui->scaleYSlider, SIGNAL(valueChanged(int)), pic, SLOT(setScaleY(int)));
    connect(ui->scaleZSlider, SIGNAL(valueChanged(int)), pic, SLOT(setScaleZ(int)));

    connect(ui->distanceSlider, SIGNAL(valueChanged(int)), pic, SLOT(setDistance(int)));
    connect(ui->kaSlider, SIGNAL(valueChanged(int)), pic, SLOT(setKa(int)));
    connect(ui->kdSlider, SIGNAL(valueChanged(int)), pic, SLOT(setKd(int)));
    connect(ui->ksSlider, SIGNAL(valueChanged(int)), pic, SLOT(setKs(int)));
    connect(ui->lightXSlider, SIGNAL(valueChanged(int)), pic, SLOT(setLightX(int)));
    connect(ui->lightYSlider, SIGNAL(valueChanged(int)), pic, SLOT(setLightY(int)));
    connect(ui->lightZSlider, SIGNAL(valueChanged(int)), pic, SLOT(setLightZ(int)));


    QVBoxLayout *l = new QVBoxLayout(ui->frame);
    l->addWidget(pic);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
