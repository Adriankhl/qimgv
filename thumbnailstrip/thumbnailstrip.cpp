#include "thumbnailstrip.h"

ThumbnailStrip::ThumbnailStrip(ImageCache *_cache, QWidget *parent) : QWidget(parent)
{
    cache = _cache;
    layout = new QHBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    connect(cache, SIGNAL(initialized()), this, SLOT(populate()));
    this->show();
}

void ThumbnailStrip::populate() {
    thumbnailLabels.clear();
    while(layout->count() > 0) {
        QLayoutItem *item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }
    for(int i=0; i<cache->length(); i++) {
        addItem(i);
    }
}

void ThumbnailStrip::addItem(int pos) {
    ThumbnailLabel *thumbLabel = new ThumbnailLabel();
    thumbLabel->setPixmap(*cache->thumbnailAt(pos));

    layout->addWidget(thumbLabel);
    thumbnailLabels.append(thumbLabel);
    connect(thumbLabel, SIGNAL(clicked(QLabel*)),
            this, SLOT(slotThumbnailClicked(QLabel*)));
}

void ThumbnailStrip::wheelEvent(QWheelEvent *event) {
    event->ignore();
}

void ThumbnailStrip::slotThumbnailClicked(QLabel* label) {
    int id = thumbnailLabels.indexOf(label);
    if(id!=-1) {
        emit thumbnailClicked(id);
    }
}

ThumbnailStrip::~ThumbnailStrip() {

}