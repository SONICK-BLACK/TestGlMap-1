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

//char *room_box[6] =
//{
//    "img/right.png",
//    "img/left.png",
//    "img/top.png",
//    "img/bottom.png",
//    "img/font.png",
//    "img/back.png",
//};

class MyGlWidget : public QGLWidget
{
    Q_OBJECT
public:

    //QStringList RoomMap;
    //номер текущей текстуры

    explicit MyGlWidget(QWidget *parent  = 0);
    ~MyGlWidget();

    void initShaders();
    void initCubeGeometry();
    void drawCube();
    void LoadCubeTexture(QStringList &filename, GLuint *target);

    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    GLuint			CurTexture;									// Идентификатор текстуры А-сканов и массив данных текстуры

    QMatrix4x4      projection;                                      //матрица системыы кооридинат
    QQuaternion     rotate;                                         //кванетрион поворота

    float xRot, yRot, zRot;
    QPoint          LastPoint;

    bool  clear_flag;												// флаг рисования пустого окна - нужен при первом включении, пока считаются лучи

    QGLShaderProgram tex_ShaderProg;								// программа шейдеров стандартного вывода текстуры
    int				 tex_Vertexes;									// атрибуы стандартного шейдера
    int				 tex_TexCoord;

};

#endif // MYGLWIDGET_H
