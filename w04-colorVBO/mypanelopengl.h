#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>

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
    void createVBOs();
    void destroyVBOs();
    void createShaders();
    void destroyShaders();

    unsigned int numVertices;
    QVector4D *vertices;

    QGLBuffer *vboVertices;

    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;

    QTimer* timer;
    float shift;


signals:
    
public slots:
   void step();
};

#endif // MYPANELOPENGL_H
