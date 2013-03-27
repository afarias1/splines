#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

//<QtOpenGL> causes some headaches.
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <QKeyEvent>
#include <QGLWidget>
#include <QMatrix4x4>
#include <QHash>
#include <QList>

#include "common/sphere.h"
#include "common/square.h"
#include "common/cylinder.h"
#include "production.h"
#include "plant.h"

typedef QVector4D point4;
typedef QVector4D color4;
typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

#define CS40_NUM_PROGS 1

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
    cs40::Cylinder* m_cylinder;
    cs40::Cylinder* m_branch;

    cs40::Plant m_plant;


    int m_polyMode;
    int m_shapeMode;

    GLuint m_textureID;
    GLuint m_normalMapID;

    vec3 m_angles; /* Euler angles for rotation */

    mat4 m_model;
    mat4 m_camera;
    mat4 m_projection;

    /* Shaders and programs */
    QGLShader *m_vertexShaders[CS40_NUM_PROGS];
    QGLShader *m_fragmentShaders[CS40_NUM_PROGS];
    QGLShaderProgram *m_shaderPrograms[CS40_NUM_PROGS];
    int m_curr_prog; //current program ID

    /* draw a simple branch */
    void drawBranch();

    /* draw sample grammar */
    void drawTree();

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
