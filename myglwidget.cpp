#include "myglwidget.h"
//------------------------------------------------------------------------------
const QString mBackImagePath = "img/back.png";
const QString mRightImagePath = "img/right.png";
const QString mLeftImagePath =  "img/left.png";
const QString mTopImagePath = "img/top.png";
const QString mBottomImagePath = "img/bottom.png";
const QString mFrontImagePath = "img/font.png";
//------------------------------------------------------------------------------
MyGlWidget::MyGlWidget(QWidget *parent) : QGLWidget(parent)
{    
    //определим парамтеры пртрици пердставления
    mLookAt.eye =    {0.0f, 0.0f, 0.0f};
    mLookAt.center = {0.0f, 0.0f, -1.0f};
    mLookAt.up =     {0.0f, 1.0f, 0.0f};

    setFocus();
}
//------------------------------------------------------------------------------
MyGlWidget::~MyGlWidget()
{
    arrayBuf.destroy();
    indexBuf.destroy();

    delete texture;
}
//------------------------------------------------------------------------------
//колмиплируем и биндим шейдеры
//------------------------------------------------------------------------------
void MyGlWidget::initShaders()
{
    //компилируем вершинные шейдер
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader_cube_map.glsl"))
        close();

    //компилириуем фрагментный шейдер
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader_cube_map.glsl"))
        close();

    //линкуем шейдеры
    if (!tex_ShaderProg.link())
        close();

    //биндим шейдеры
    if (!tex_ShaderProg.bind())
        close();
}
//------------------------------------------------------------------------------
//загружаем стандартную текстуру
//------------------------------------------------------------------------------
void MyGlWidget::initTexure()
{
    texture = new QOpenGLTexture(QImage(":/img/back.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//------------------------------------------------------------------------------
//загружаем стандартную текууру для скайбокса
//------------------------------------------------------------------------------
void MyGlWidget::LoadCubeTexture()
{
    //создаем QIMage для каждой грани (x pos/ neg, y pos/ neg, z pos/ neg)
//    const QImage posx = QImage(mRightImagePath).convertToFormat(QImage::Format_RGBA8888);
//    const QImage negx = QImage(mLeftImagePath).convertToFormat(QImage::Format_RGBA8888);

//    const QImage posy = QImage(mTopImagePath).convertToFormat(QImage::Format_RGBA8888);
//    const QImage negy = QImage(mBottomImagePath).convertToFormat(QImage::Format_RGBA8888);

//    const QImage posz = QImage(mFrontImagePath).convertToFormat(QImage::Format_RGBA8888);
//    const QImage negz = QImage(mBackImagePath).convertToFormat(QImage::Format_RGBA8888);


    const int width = 100;
    const int height = 100;

    QImage posx = QImage(width, height, QImage::Format_RGBA8888);
    posx.fill(Qt::blue);
    QImage negx = QImage(width, height, QImage::Format_RGBA8888);
    negx.fill(Qt::green);

    QImage posy = QImage(width, height, QImage::Format_RGB32);
    posy.fill(Qt::red);
    QImage negy = QImage(width, height, QImage::Format_RGB32);
    negy.fill(Qt::green);

    QImage posz = QImage(width, height, QImage::Format_RGB32);
    posz.fill(Qt::green);
    QImage negz = QImage(width, height, QImage::Format_RGB32);
    negz.fill(Qt::green);

    uchar data[width][height];
    memset(data, 0x355E3B, sizeof(data));

  //  texture = new QOpenGLTexture(posz);
//    texture->create();
//    texture->setSize(width, height);
//    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
//    texture->allocateStorage();

    //создаем тестуру в видеопамяти
    glGenTextures(1, &hdTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, hdTexture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //гризми тексутуру для каждой из шести гранией куба
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posx.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posy.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negy.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posz.constBits());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negz.constBits());

    //texture->bind();

//    texture->generateMipMaps();
//    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
//    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
//    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);

    //загржаем данные изображения грани в соответсвующий участок текстуры
//    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     posx.constBits(), Q_NULLPTR);

//    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     posy.constBits(), Q_NULLPTR);

//    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     posz.constBits(), Q_NULLPTR);

//    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     negx.constBits(), Q_NULLPTR);

//    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     negy.constBits(), Q_NULLPTR);

//    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
//                     QOpenGLTexture::RGBA, QOpenGLTexture::UInt8,
//                     negz.constBits(), Q_NULLPTR);

}
//------------------------------------------------------------------------------
//загружаем текууру для скайбокса, по указаннаму набору файлво текстур
//------------------------------------------------------------------------------
void MyGlWidget::LoadCubeTexture(QString path)
{

    //создаем QIMage для каждой грани (x pos/ neg, y pos/ neg, z pos/ neg)
    //для каждой грани указаываем название соотвестувющего файла,
    //название формируется в фомрате path +  top, bottom ...

//    const QImage posx = QImage(path + "/top.png").convertToFormat(QImage::Format_RGBA8888);
//    const QImage negx = QImage(path + "/right.png").convertToFormat(QImage::Format_RGBA8888);

//    const QImage posy = QImage(path + "/left.png").convertToFormat(QImage::Format_RGBA8888);
//    const QImage negy = QImage(path + "/front.png").convertToFormat(QImage::Format_RGBA8888);

//    const QImage posz = QImage(path + "/bootom.png").convertToFormat(QImage::Format_RGBA8888);
//    const QImage negz = QImage(path + "/back.png").convertToFormat(QImage::Format_RGBA8888);

//    const int width = 100;
//    const int height = 100;

//    //texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);

////    texture->create();
////    texture->setSize(width, height);
////    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
////    texture->allocateStorage();
////    hdTexture = texture->textureId();
////    qDebug() << "hetx" << hdTexture;

//    //создаем тестуру в видеопамяти
//    glGenTextures(1, &hdTexture);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, hdTexture);

//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

//    //гризми тексутуру для каждой из шести гранией куба
//   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posx.constBits());
//    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negx.constBits());
//    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posy.constBits());
//    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negy.constBits());
//    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, posz.constBits());
//    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
//             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, negz.constBits());
}
//------------------------------------------------------------------------------
//ниницализурем геометрию куба
//------------------------------------------------------------------------------
void MyGlWidget::initCubeGeometry()
{
    //заполяем  указываем вершинные и  текстурные координаты для каждой точки
    VertexData vertices[] = {

        //передняя грань
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        //правая грань
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        //задняя грань
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        //левая грань
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        //нижняя грань
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        //верзняя грань
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));
}
//------------------------------------------------------------------------------
//иницаилизируем емоетрию сканйбокса
//------------------------------------------------------------------------------
void MyGlWidget::initSkyBoxGeometry()
{
    //в скайбоксе вершинные и текстурные координтаы совпдадают
    QVector3D vertices[] = {
        {-1.0f,  1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},

        {-1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, -1.0f, +1.0f},

        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},

        {-1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},

        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},

        {-1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f}

    };


    arrayBuf.bind();
    arrayBuf.allocate(vertices, 36 * sizeof(QVector3D));

    //генарируем массив аттриуботв заданных индксов
    int vertexLocation = tex_ShaderProg.attributeLocation("a_position");
    tex_ShaderProg.enableAttributeArray(vertexLocation);
    tex_ShaderProg.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));
}
//------------------------------------------------------------------------------
//процедура рисвания куба с кубичксокгй текстурой
//------------------------------------------------------------------------------
void MyGlWidget::drawCube()
{
    //биндим VBO
    arrayBuf.bind();
    indexBuf.bind();

    //загрузим массив координат куба
    quintptr offset = 0;

    int vertexLocation = tex_ShaderProg.attributeLocation("a_position");
    tex_ShaderProg.enableAttributeArray(vertexLocation);
    tex_ShaderProg.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//    //определяем текутурные координаты
    offset += sizeof(QVector3D);

    int texcoordLocation = tex_ShaderProg.attributeLocation("a_texcoord");
    tex_ShaderProg.enableAttributeArray(texcoordLocation);
    tex_ShaderProg.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));


    //рисуем куб по массиву индексов, храняще муся в VBO1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
//------------------------------------------------------------------------------
//процедура отсриовки скайбокса
//------------------------------------------------------------------------------
void MyGlWidget::drawSkyBox()
{
    //отоключаем буффер глубины
    glDepthMask(GL_FALSE);
    //рисуем куб по массиву индексов, храняще муся в VBO1
    glDrawArrays(GL_TRIANGLES,  0, 36);
    glDepthMask(GL_TRUE);
}
//------------------------------------------------------------------------------
//инициализируем фугкиции opnenGl,
//создаем  обьекты класса геометрических памрамтеров,
// компилируем шейдерные прогрмммы
//------------------------------------------------------------------------------
void MyGlWidget::initializeGL()
{
    QGLFunctions *f = context()->functions();
    f->initializeGLFunctions();
    glClearColor(0, 1, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    //создадим тесктуру
    LoadCubeTexture();

    //рассичтаем геметрию куба
    arrayBuf.create();
    initSkyBoxGeometry();
}
//------------------------------------------------------------------------------
void MyGlWidget::resizeGL(int w, int h)
{
    //обновляем размеры канвы
    glViewport(0,0, w, h);

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 100.0, fov = 60.0;

    //утснавливаем парматреы облсти отрсивки
    mPerspective.verticalAngle = fov;
    mPerspective.farPlane = zFar;
    mPerspective.nearPlane = zNear;
    mPerspective.aspectRatio = aspect;

    updateGL();
}
//------------------------------------------------------------------------------
void MyGlWidget::paintGL()
{
    //makeCurrent();

    QGLFunctions *f = context()->functions();

    // очщаем буфферы
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP, hdTexture);
    f->glActiveTexture(GL_TEXTURE0);
    //texture->bind();

    //обновляем парметры перспективной матрицы
    static QMatrix4x4 mProjectionMat;
    mProjectionMat.setToIdentity();
    mProjectionMat.perspective(mPerspective.verticalAngle,
       mPerspective.aspectRatio,
       mPerspective.nearPlane,
       mPerspective.farPlane);

    //конфигурируем мтрицу видового предсатнвления
    //на основе позиции камеры и угла поворота    
    static QMatrix4x4 mViewMat;
    mViewMat.setToIdentity();
    mViewMat.lookAt(mLookAt.eye,
            mLookAt.center,
            mLookAt.up);

    //утснваим аттрибуты шейдера
    tex_ShaderProg.setUniformValue("texture", 0);
    tex_ShaderProg.setUniformValue("mvp_matrix", mProjectionMat * mViewMat);

    drawSkyBox();

   // swapBuffers();
}
//------------------------------------------------------------------------------
void MyGlWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    LastPoint = event->pos();
}
//------------------------------------------------------------------------------
void MyGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    double x_rot = 1 / M_PI * (event->pos().y() - LastPoint.y());
    double y_rot = 1 / M_PI * (event->pos().x() - LastPoint.x());
    QVector3D AxisX = QVector3D(1, 0, 0);
    QVector3D AxisY = QVector3D(0, 1, 0);

    //стчиаем кватериан как произведение кватерианов
    //поворта вокруг каждых осей
    QQuaternion rotate = QQuaternion::fromAxisAndAngle(AxisX, x_rot)
            * QQuaternion::fromAxisAndAngle(AxisY, y_rot);

    //рассичтаем параматреы видовой матрицы
    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.rotate(rotate);

    mLookAt.center = {0.0f, 0.0f, -1.0f};
    mLookAt.center = mLookAt.center * mat;

    updateGL();
}
//------------------------------------------------------------------------------
//void MyGlWidget::mouseReleaseEvent(QMouseEvent *event)
//{

//}
//------------------------------------------------------------------------------
void MyGlWidget::keyPressEvent(QKeyEvent *event)
{
    event->accept();

    //вращем камеру вокруг оси У по часовой стрелке
    int dir = 1;
    static float angle = 0.0;

    if (event->key() == Qt::Key_F5){
        dir = 1;
    }
    else if (event->key() == Qt::Key_F6) {
        dir = -1;
    }
    else return;

    QVector3D AxisY = QVector3D(0, 1, 0);
    angle += 1 / M_PI * (10*dir);
    //считаем кватерион повората
    QQuaternion rotate = QQuaternion::fromAxisAndAngle(AxisY, angle);

    //рассичтаем параматреы видовой матрицы
    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.rotate(rotate);

    mLookAt.center = {0.0f, 0.0f, -1.0f};
    mLookAt.center = mLookAt.center * mat;

    updateGL();
}
//------------------------------------------------------------------------------
void MyGlWidget::wheelEvent(QWheelEvent *event)
{
    float delta = event->delta() > 0 ? -5.0f : +5.0f;
    mPerspective.verticalAngle += delta;
    if(mPerspective.verticalAngle < 10.0f)
        mPerspective.verticalAngle = 10.0f;
    else if(mPerspective.verticalAngle > 120.0f)
        mPerspective.verticalAngle = 120.0f;

    updateGL();
}
//------------------------------------------------------------------------------
