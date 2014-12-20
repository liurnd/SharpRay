#include "imageviewer.h"
#include <QMouseEvent>
ImageViewer::ImageViewer(QWidget *parent) :
    QLabel(parent)
{
}


void ImageViewer::mousePressEvent(QMouseEvent *ev)
{
    emit clicked(ev->pos());
}
