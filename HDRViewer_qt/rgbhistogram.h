#ifndef RGBHISTOGRAM_H
#define RGBHISTOGRAM_H

#include <QWidget>
#define PixelDeep 256

class RGBHistogram : public QWidget
{
    Q_OBJECT
private:
    int RCnt[PixelDeep];
    int BCnt[PixelDeep];
    int GCnt[PixelDeep];
    int GrayCnt[PixelDeep];
    int maxNum;
    void calcDelta();
    void drawHistLine(QPainter& p, Qt::GlobalColor color,float value, int cnt);
protected:
    void RGBHistogram::paintEvent(QPaintEvent *e);
public:
    explicit RGBHistogram(QImage* image, QWidget *parent = 0);
    QImage* targetImage;

    float DeltaX, DeltaY;
    int margin,barHeight;
    int barBeginX, barEndX, barY;
signals:

public slots:
    void updateImage();
    void updateImage(QImage*);
};

#endif // RGBHISTOGRAM_H
