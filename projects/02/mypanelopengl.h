#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>
#include "triangle.h"

class MyPanelOpenGL : public QGLWidget
{
    Q_OBJECT

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:

    void createShaders();
    void destroyShaders();

    void createVBOs();
    void destroyVBOs();
    QGLBuffer *vboVertices;
    unsigned int numVertices;
    QVector2D *vertices;

    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;
 
    cs40::Triangle* tri;


signals:
    
public slots:

};

#endif // MYPANELOPENGL_H
