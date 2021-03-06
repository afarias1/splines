#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

//<QtOpenGL> causes some headaches.
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <QKeyEvent>
#include <QGLWidget>
#include <QMatrix4x4>
#include "common/sphere.h"
#include "common/square.h"

typedef QVector4D point4;
typedef QVector4D color4;
typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

#define CS40_NUM_PROGS 2
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
    int m_normal_map;
    bool m_drawSphere;

    GLuint m_textureID;
    GLuint m_normalMapID1;
    GLuint m_normalMapID2;

    vec3 m_angles; /* Euler angles for rotation */

    mat4 m_model;
    mat4 m_camera;
    mat4 m_projection;

    /* Shaders and programs */
    QGLShader *m_vertexShaders[CS40_NUM_PROGS];
    QGLShader *m_fragmentShaders[CS40_NUM_PROGS];
    QGLShaderProgram *m_shaderPrograms[CS40_NUM_PROGS];
    int m_curr_prog; //current program ID


    /* update Euler angle at index idx by amt
     * idx=0,1,2 -> x,y,z */
    void updateAngles(int idx, qreal amt);

    /* update model matrix based on angle */
    void updateModel();

    /* wrap a angle value to the range 0..360*/
    qreal wrap(qreal amt);

    /* update Polygon draw mode based
     * 0 : point
     * 1 : line
     * 2 : polygon */
    void updatePolyMode(int val);

    void createShaders(int i, QString vertName, QString fragName);
    void destroyShaders(int i);

signals:
    
public slots:

};

#endif // MYPANELOPENGL_H
