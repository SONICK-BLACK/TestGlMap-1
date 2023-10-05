#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#pragma once

#include <QtOpenGl/QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <QtGui>
#include <QOpenGLContext>
#include <QOpenGLWidget>
#include "GL/gl.h"
#include <qgl.h>
#include <QMouseEvent>

class MyGlWidget : public QGLWidget
{
    Q_OBJECT
public:


    explicit MyGlWidget(QWidget *parent  = 0);
    ~MyGlWidget();

    void initShaders();

    void LoadCubeTexture();
    void LoadCubeTexture(QString path);
    void initTexure();

    void initCubeGeometry();
    void initSkyBoxGeometry();

    void drawCube();
    void drawSkyBox();

    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:

    struct
    {
        float verticalAngle;
        float aspectRatio;
        float nearPlane;
        float farPlane;
    } mPerspective;

    struct
    {
        QVector3D eye;
        QVector3D center;
        QVector3D up;
    } mLookAt;

    struct VertexData
    {
        QVector3D position;
        QVector3D texCoord;
    };

    QOpenGLTexture  *texture;                                       //текстура кубмапап
    GLuint          hdTexture;                                       //хендл текстуры
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    //QMatrix4x4      mViewMat;                                          //матрица камеры (полдение камаеры в простнстве, угол поворита камеры)
    //QMatrix4x4      mProjectionMat;                                    //матрица перспектинвой проэкции облсасти отрисовки
    //QQuaternion     rotate;                                         //кванетрион поворота

    QPoint          LastPoint;

    QGLShaderProgram tex_ShaderProg;								// программа шейдеров стандартного вывода текстуры
    int				 tex_Vertexes;									// атрибуы стандартного шейдера
    int				 tex_TexCoord;

    bool  clear_flag;												// флаг рисования пустого окна - нужен при первом включении, пока считаются лучи

};

#endif // MYGLWIDGET_H
