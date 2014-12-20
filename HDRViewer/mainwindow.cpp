#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gamma = 1;
    ISO = 200;

    maxISO = 12800;
    isoLogBase = 1.2f;
    isoFactor = maxISO / pow(isoLogBase, ui->ISOValueSlider->maximum());

    ui->ISOValueSlider->setValue(ISO2level(ISO));
    ui->gammaFactorSlider->setValue(gamma*100);
    ui->ISOValue->setText(QString("%1").arg(ISO));
    ui->gammaFactor->setText(QString("%1").arg(gamma));

    displayGround = new ImageViewer();
    displayGround->show();

    hist = new RGBHistogram(NULL, ui->histWidget);

    pixelList = NULL;
    image = NULL;

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(doOpenFile()));
    connect(ui->ISOValueSlider, SIGNAL(valueChanged(int)),this,SLOT(changeParam()));
    connect(ui->gammaFactorSlider,SIGNAL(valueChanged(int)),this,SLOT(changeParam()));
    connect(displayGround,SIGNAL(clicked(QPoint)),this,SLOT(clickOnPic(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

float MainWindow::level2ISO(int l)
{
    return isoFactor * pow(isoLogBase, l);
}

void MainWindow::changeParam()
{
    ISO = level2ISO(ui->ISOValueSlider->value());
    gamma = static_cast<float>(ui->gammaFactorSlider->value()) / 100;

    updateImage();

    ui->ISOValue->setText(QString("%1").arg(ISO));
    ui->gammaFactor->setText(QString("%1").arg(gamma));
}

void MainWindow::doOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image File"),
                                                    QString(),
                                                    tr("HDR File (*.hdr)"));
    FILE* fin = fopen(fileName.toStdString().c_str(), "rb");
    if (fin == NULL)
        return ;

    fread(&imgWidth,sizeof(imgWidth), 1, fin);
    fread(&imgHeight,sizeof(imgHeight), 1, fin);
    if (pixelList != NULL) delete [] pixelList;
    pixelList = new HDRPixel[imgWidth*imgHeight];
    pixelCnt = 0;
    while(1)
    {
        size_t cnt = fread(pixelList,sizeof(HDRPixel), imgWidth*imgHeight, fin);
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

void MainWindow::clickOnPic(QPoint pos)
{
    QRgb pixel = image->pixel(pos);
    ui->infoBox->setText(QString("X:%1\nY:%2\nR:%3 B:%4 G:%5")
                         .arg(pos.x()).arg(pos.y())
                         .arg(qRed(pixel)).arg(qBlue(pixel)).arg(qGreen(pixel)));

}
