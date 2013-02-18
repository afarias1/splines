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
    void keyPressEvent(QKeyEvent* event);

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:

    unsigned int numVertices;
    point4* points; /* for vbo */
    color4* colors; /* for vbo */
    vec3 angles; /* Euler angles for rotation */

    point4 *vertices; /* unique cube vertices */
    color4 *vertex_colors; /* unique cube colors */

    /* GPU data for shaders */
    QGLBuffer *vboData;

    /* Shaders and program */
    QGLShader *vertexShader;
    QGLShader *fragmentShader;
    QGLShaderProgram *shaderProgram;

    /* Build a model of a unit cube centered at the origin*/
    void makeCube();

    /* Construct geometry/colors for one face of cube,
     * given vertex indices in CCW order */
    void quad(int a, int b, int c, int d );

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
