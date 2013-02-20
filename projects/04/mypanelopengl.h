#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QGLWidget>
#include <QtOpenGL>
#include "sphere.h"
#include "square.h"
#include "matrixstack.h"

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

    /* simple test shapes */
    cs40::Sphere* m_sphere;
    cs40::Square* m_square;

    int m_polymode;
    int m_texture;
    bool m_drawSphere;

    GLuint m_textureID;

    QMatrix4x4 m_model; /* Takes objects coordinates into world coordinates */
    QMatrix4x4 m_view; /* Takes world coordinates into clip coordinates */
    cs40::MatrixStack m_modelStack; /* history of past model matrices */


    vec3 m_angles; /* Euler angles for rotation */

    /* Shaders and program */
    QGLShader *m_vertexShader;
    QGLShader *m_fragmentShader;
    QGLShaderProgram *m_shaderProgram;

    /* update Euler angle at index idx by amt
     * idx=0,1,2 -> x,y,z */
    void updateAngles(int idx, qreal amt);

    /* wrap a angle value to the range 0..360*/
    qreal wrap(qreal amt);

    /* update Polygon draw mode based
     * 0 : point
     * 1 : line
     * 2 : polygon */
    void updatePolyMode(int val);

    void createVBO();
    void destroyVBO();
    void createShaders();
    void destroyShaders();

signals:
    
public slots:

};

#endif // MYPANELOPENGL_H
