#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>
#include "sphere.h"

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
    void keyPressEvent(QKeyEvent* event);

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:

    cs40::Sphere* m_sphere;

    vec3 angles; /* Euler angles for rotation */

    /* Shaders and program */
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;

    /* update Euler angle at index idx by amt
     * idx=0,1,2 -> x,y,z */
    void updateAngles(int idx, qreal amt);

    /* wrap a angle value to the range 0..360*/
    qreal wrap(qreal amt);

    void createVBO();
    void destroyVBO();
    void createShaders();
    void destroyShaders();

signals:
    
public slots:

};

#endif // MYPANELOPENGL_H
