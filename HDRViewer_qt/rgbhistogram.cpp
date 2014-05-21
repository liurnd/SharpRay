#include "rgbhistogram.h"
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QDebug>
RGBHistogram::RGBHistogram(QImage *image, QWidget *parent) :
    targetImage(image), QWidget(parent)
{
    barHeight = 4;
    margin = 2;
    resize(parent->size());
}

void RGBHistogram::calcDelta()
{
    DeltaX = (float)(width() - 2 * margin) / PixelDeep;
    DeltaY = (float)(height() - 2 * margin - barHeight) / maxNum;
    barBeginX = margin;
    barEndX = barBeginX + PixelDeep * DeltaX;
    barY = height() - margin - barHeight / 2;
}


void RGBHistogram::updateImage(QImage* i)
{
    targetImage = i;
    updateImage();

}

void RGBHistogram::updateImage()
{
    memset(RCnt,0,sizeof(RCnt));
    memset(GCnt,0,sizeof(GCnt));
    memset(BCnt,0,sizeof(BCnt));
    memset(GrayCnt,0,sizeof(GrayCnt));


    for(int j = 0; j < targetImage->height(); j++)
        for(int i = 0 ; i < targetImage->width();i++)
        {
            QRgb c = targetImage->pixel(i,j);
            RCnt[qRed(c)]++;
            BCnt[qBlue(c)]++;
            GCnt[qGreen(c)]++;
            GrayCnt[qGray(c)]++;
        }
    for (int i = 0; i < PixelDeep; i++)
        maxNum = std::max(std::max(std::max(RCnt[i],BCnt[i]),std::max(GCnt[i],GrayCnt[i])),maxNum);
    repaint();
}

void RGBHistogram::drawHistLine(QPainter& p, Qt::GlobalColor color,float value, int cnt)
{
    QPen(QBrush(color),ceil(DeltaX));
    p.drawLine(value,barY - DeltaY*cnt,value, barY);
}

void RGBHistogram::paintEvent(QPaintEvent *e)
{
    if (targetImage == NULL)
        return;
    calcDelta();
    QPainter p(this);

    float x = barBeginX;
    for (int i = 0; i < PixelDeep;i++)
    {

        drawHistLine(p,Qt::red, x,RCnt[i]);
        drawHistLine(p,Qt::blue, x,BCnt[i]);
        drawHistLine(p,Qt::green, x,GCnt[i]);
        drawHistLine(p,Qt::gray, x,GrayCnt[i]);

        x += DeltaX;
    }
    p.drawLine(barBeginX,barY, barEndX, barY);
    p.drawLine(barBeginX,barY,barBeginX,barY+barHeight);
    p.drawLine(barEndX,barY,barEndX,barY+barHeight);
}


