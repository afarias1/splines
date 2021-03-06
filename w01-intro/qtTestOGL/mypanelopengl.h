#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>

class MyPanelOpenGL : public QGLWidget
{
    Q_OBJECT
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    int sides;
    double radius;


public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    
signals:
    
public slots:
    void changeSides(int s);
    void changeRadius(double r);
};

#endif // MYPANELOPENGL_H
