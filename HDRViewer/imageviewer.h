#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QLabel>

class ImageViewer : public QLabel
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *ev);
signals:
    void clicked(QPoint pos);
public slots:

};

#endif // IMAGEVIEWER_H
