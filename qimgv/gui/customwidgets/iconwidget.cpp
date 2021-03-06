#include "iconwidget.h"

IconWidget::IconWidget(QWidget *parent)
    : QWidget(parent),
      hiResPixmap(false),
      pixmap(nullptr)
{
    dpr = this->devicePixelRatioF();
}

IconWidget::~IconWidget() {
    if(pixmap)
        delete pixmap;
}

void IconWidget::setIconPath(QString path) {
    if(pixmap)
        delete pixmap;
    if(dpr >= (1.0 + 0.001)) {
        path.replace(".", "@2x.");
        hiResPixmap = true;
        pixmap = new QPixmap(path);
        if(dpr >= (2.0 - 0.001))
            pixmapDrawScale = dpr;
        else
            pixmapDrawScale = 2.0;
        pixmap->setDevicePixelRatio(pixmapDrawScale);
    } else {
        hiResPixmap = false;
        pixmap = new QPixmap(path);
        pixmapDrawScale = dpr;
    }
    update();
}

void IconWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if(pixmap) {
        //p.fillRect(rect(), QBrush(QColor(100,100,200,255)));
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        QPointF pos;
        if(hiResPixmap) {
            pos = QPointF(width()  / 2 - pixmap->width()  / (2 * pixmapDrawScale),
                          height() / 2 - pixmap->height() / (2 * pixmapDrawScale));
        } else {
            pos = QPointF(width()  / 2 - pixmap->width()  / 2,
                          height() / 2 - pixmap->height() / 2);
        }
        p.drawPixmap(pos, *pixmap);
    }
}
