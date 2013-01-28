#ifndef MYIMAGEBOX_H
#define MYIMAGEBOX_H

#include <QWidget>
#include <QtGui>

class MyImageBox : public QWidget
{
    Q_OBJECT
public:
    explicit MyImageBox(QWidget *parent = 0);
    
signals:
    
public slots:
    void open();
    void fitClicked(bool isSet);

private:
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QGridLayout *layout;

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    bool fitToWin;
    double scaleFactor;
    
};

#endif // MYIMAGEBOX_H
