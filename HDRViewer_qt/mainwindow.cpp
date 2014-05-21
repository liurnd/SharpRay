#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(doOpenFile()));
    gamma = 1;
    ISO = 200;
    displayGround = new QLabel();
    displayGround->show();

    hist = new RGBHistogram(NULL, ui->histWidget);

    pixelList = NULL;
    image = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image File"),
                                                    QString(),
                                                    tr("HDR File (*.hdr)"));
    FILE* fin = fopen(fileName.toStdString().c_str(), "rb");
    fread(&imgWidth,sizeof(imgWidth), 1, fin);
    fread(&imgHeight,sizeof(imgHeight), 1, fin);
    if (pixelList != NULL) delete [] pixelList;
    pixelList = new HDRPixel[imgWidth*imgHeight];
    while(1)
    {
        int cnt = fread(pixelList,sizeof(HDRPixel), imgWidth*imgHeight, fin);
        if (cnt <= 0)
            break;
        pixelCnt+=cnt;
    }
    fclose(fin);

    if (image!=NULL) delete image;
    image = new QImage(imgWidth,imgHeight,QImage::Format_RGB32);
    updateImage();
}

void MainWindow::updateImage()
{
    for (int i = 0; i < pixelCnt; i++)
    {
        HDRPixel& pixel = pixelList[i];
        auto t = pixel.getColor(gamma,ISO);
        image->setPixel(pixel.x,pixel.y,t.rgb());
    }

    hist->updateImage(image);

    displayGround->setPixmap(QPixmap::fromImage(*image));
    displayGround->resize(imgWidth,imgHeight);
    displayGround->show();
}
