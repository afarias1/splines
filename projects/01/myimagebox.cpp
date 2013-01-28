#include "myimagebox.h"

MyImageBox::MyImageBox(QWidget *parent) :
    QWidget(parent)
{
     imageLabel = new QLabel();
     //imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     imageLabel->setScaledContents(true);


     scrollArea = new QScrollArea(this);
     scrollArea->setWidget(imageLabel);
     scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     scrollArea->show();

     layout = new QGridLayout;
     layout->setContentsMargins(0,0,0,0);
     layout->addWidget(scrollArea);
     setLayout(layout);


}

void MyImageBox::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), QDir::currentPath());

     if (!fileName.isEmpty()) {
         QImage image(fileName);
         if (image.isNull()) {
             QMessageBox::information((QWidget*)parent(), tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(fileName));
             return;
         }

         imageLabel->setPixmap(QPixmap::fromImage(image));
         imageLabel->adjustSize();
         scaleFactor = 1.0;
     }
}

void MyImageBox::fitClicked(bool isSet){

    if(isSet){
        //scrollArea->setWidgetResizable(isSet);
        QSize iSize=imageLabel->pixmap()->size();
        QSize scSize = scrollArea->size();
        iSize.scale(scSize, Qt::KeepAspectRatio);
        imageLabel->resize(iSize);
    }
    else{
        imageLabel->adjustSize();
        scaleFactor = 1.0;
    }
}

void MyImageBox::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

}

void MyImageBox::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
