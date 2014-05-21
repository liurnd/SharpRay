#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>
#include <math.h>
#include <QLabel>
#include "rgbhistogram.h"

struct HDRPixel{
    int x, y;
    float r, g, b;
    QColor getColor(float gamma, float ISO)
    {
        uint8_t tmpR, tmpG, tmpB;
        float Rr, Rb, Rg;
        Rr = pow((r * ISO), gamma)*255;
        Rb = pow((b * ISO), gamma)*255;
        Rg = pow((g * ISO), gamma)*255;
        tmpR = Rr > 255 ? (uint8_t)255 : (uint8_t)Rr;
        tmpG = Rg > 255 ? (uint8_t)255 : (uint8_t)Rg;
        tmpB = Rb > 255 ? (uint8_t)255 : (uint8_t)Rb;
        return QColor::fromRgb(tmpR, tmpG, tmpB);
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int imgWidth; int imgHeight;
    int pixelCnt;
    HDRPixel* pixelList;
    QImage* image;
    QLabel* displayGround;
    RGBHistogram* hist;

    float ISO, gamma;

    float ISO2level(float);
    float level2ISO(float);
public slots:
    void doOpenFile();
    void updateImage();
    void changeParam(){}
};



#endif // MAINWINDOW_H
