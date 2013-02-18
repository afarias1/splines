#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>

typedef QVector4D point4;
typedef QVector4D color4;
typedef QVector3D vec3;

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
    void createVBO();
    void destroyVBO();
    void createShaders();
    void destroyShaders();


    void quad(int a, int b, int c, int d );
    void makeCube();

    unsigned int numVertices;
    point4* points;
    color4* colors;

    point4 *vertices;
    color4 *vertex_colors;
    vec3 angles;

    QGLBuffer *vboData;

    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;

signals:
    
public slots:

};

#endif // MYPANELOPENGL_H
