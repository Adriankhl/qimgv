#include "sidepanel.h"
#include "ui_sidepanel.h"

SidePanel::SidePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SidePanel),
    mWidget(NULL)
{
    ui->setupUi(this);
    this->setObjectName("SidePanel");
    this->hide();
}

SidePanel::~SidePanel()
{
    delete ui;
}

void SidePanel::setWidget(QWidget* w) {
    if(mWidget) {
        mWidget->hide();
        ui->layout->removeWidget(mWidget);
    }
    mWidget = w;
    ui->layout->addWidget(w);
    w->show();
}

QWidget* SidePanel::widget() {
    return mWidget;
}

void SidePanel::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}