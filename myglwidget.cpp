#include "myglwidget.h"
#include <QStringList>
//------------------------------------------------------------------------------
//QString img_back = QString(":/img/back.png");
//QString img_front = QString(":/img/front.png");
//QString img_top = QString(":/img/top.png");
//QString img_bot = QString("");
//QString img_left = QString("");
//QString img_right = QString("");
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};
//------------------------------------------------------------------------------
MyGlWidget::MyGlWidget(QWidget *parent)
    : QGLWidget(parent)
{    
}
//------------------------------------------------------------------------------
MyGlWidget::~MyGlWidget()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//------------------------------------------------------------------------------
//инициализируем фугкиции opnenGl,
//создаем  обьекты класса геометрических памрамтеров,
// компилируем шейдерные прогрмммы
//------------------------------------------------------------------------------
void MyGlWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);

    //создаем тесутруу
    QGLFunctions *f = context()->functions();

    glEnable(GL_TEXTURE_2D);
    f->glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &CurTexture);
    glBindTexture(GL_TEXTURE_2D, CurTexture);

    QImage mtez(100, 100, QImage::Format_ARGB32);
    mtez.fill(Qt::blue);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mtez.width(), mtez.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (uchar*)mtez.scanLine(0));
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//    QGLShader *tex_v_shader = new QGLShader(QGLShader::Vertex);
//    tex_v_shader->compileSourceFile(":/vshader.glsl");

//    QGLShader *tex_f_shader = new QGLShader(QGLShader::Fragment);
//    tex_f_shader->compileSourceFile(":/fshader.glsl");

//    // компилируем шейдеры
//    tex_ShaderProg.addShader(tex_v_shader);
//    tex_ShaderProg.addShader(tex_f_shader);
//    tex_ShaderProg.link();

    initShaders();

    //виделим врешнные буфферы в видеопамяти
    arrayBuf.create();
    indexBuf.create();

    //рассичтаем геметрию куба
    initCubeGeometry();

//    QStringList RoomMap = {
//        QString(":/img/right.png"),
//        QString(":/img/left.png"),
//        QString(":/img/top.png"),
//        QString(":/img/bottom.png"),
//        QString(":/img/font.png"),
//        QString(":/img/back.png")
//    };


    //создадим старнартную текстуру
    //LoadCubeTexture(RoomMap, &CurTexture);    

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}
//------------------------------------------------------------------------------
void MyGlWidget::initShaders()
{
    // Compile vertex shader
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!tex_ShaderProg.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!tex_ShaderProg.link())
        close();

    // Bind shader pipeline for use
    if (!tex_ShaderProg.bind())
        close();
}
//------------------------------------------------------------------------------
//загружаем текууры для скайбокса
//------------------------------------------------------------------------------
void MyGlWidget::LoadCubeTexture(QStringList &filename, GLuint *target)
{
    //ситчаем данные файлво в соответсвующие QIMAge
//    QList<QImage> images;

//    for (int i = 0; i <6; i++)
//    {
//        QImage img = QImage(filename.at(i));
//        images.append(img);
//    }

    QGLFunctions *f = context()->functions();

    //выделям в видеопамяти месото под текстуру с указаным хендлом
    glGenTextures(1, target);
    //биндм текстурур
    glBindTexture(GL_TEXTURE_CUBE_MAP, *target);
    f->glActiveTexture(GL_TEXTURE0);

    //утсанвливаем парметр, помогающий избежать артефактов на границе тексур
    //при отрисвоке с помощью линейной интерполяции
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_NEAREST);
    //параметр MAG фильтр определяютс поведение текстур ы при растягивании
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //ширину и высоту берем по первому изобрадению
    //ибо текстуры имеют одинаковый размере
//        int width = images.at(0).width();
//        int height = images.at(0).height();
    //int cnt = 0;

    QImage mming(100, 100, QImage::Format_ARGB32);
    mming.fill(Qt::blue);
    int width = mming.width();
    int height = mming.height();
    uchar *data;

    //загружаем данные тексуры в видеопамять
//    for (int i = 0; i < 6; i++)
//    {
        data = (uchar*)mming.scanLine(0);
        //POSITIVE_X - код правой грани текстуры,
        //все последующеи коды идут подряд
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                     0, GL_RGB, width, height,
                     0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);

    //}

    //glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
//------------------------------------------------------------------------------
//инициализируем геметрию куба
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

//    // Индексы для рисования граней куба с помощью треугольников.
//    // Треугольники можно соединить дублированием индексов
//    // между полосками. Если соединительные полосы расположены противоположно
//    // порядок вершин, затем последний индекс первой полосы и первый
//    // индекс второй полоски необходимо продублировать. Если
//    // соединительные полосы имеют тот же порядок вершин, только последний
//    // индекс первой полосы необходимо продублировать.
//    GLushort indices[] = {
//         0,  1,  2,  3,  3,     // передняя грань 0 - triangle strip ( v0,  v1,  v2,  v3)
//         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
//         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
//        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
//        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
//        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
//    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    //indexBuf.bind();
    //indexBuf.allocate(indices, 34 * sizeof(GLushort));

}
//------------------------------------------------------------------------------
//процедура рисвания куба с кубичксокгй текстурой
//------------------------------------------------------------------------------
void MyGlWidget::drawCube()
{

    // Индексы для рисования граней куба с помощью треугольников.
    // Треугольники можно соединить дублированием индексов
    // между полосками. Если соединительные полосы расположены противоположно
    // порядок вершин, затем последний индекс первой полосы и первый
    // индекс второй полоски необходимо продублировать. Если
    // соединительные полосы имеют тот же порядок вершин, только последний
    // индекс первой полосы необходимо продублировать.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // передняя грань 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    QGLFunctions *f = context()->functions();

    // загрузим текстуру А-сканов
//    glEnable(GL_TEXTURE_2D);
//    glClear(GL_COLOR_BUFFER_BIT); // чистим буфер

//    f->glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, CurTexture);

    //биндим VBO
    arrayBuf.bind();
    //indexBuf.bind();

    //загрузим массив координат куба
    quintptr offset = 0;

    int vertexLocation = tex_ShaderProg.attributeLocation("a_position");
    tex_ShaderProg.enableAttributeArray(vertexLocation);
    tex_ShaderProg.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = tex_ShaderProg.attributeLocation("a_texcoord");
    tex_ShaderProg.enableAttributeArray(texcoordLocation);
    tex_ShaderProg.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    //рисуем куб по массиву индексов, храняще муся в VBO1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, indices);
}
//------------------------------------------------------------------------------
void MyGlWidget::resizeGL(int w, int h)
{
    //обновляем размеры канвы
    glViewport(0,0, w, h);

    //расситчаем матрицу сиситемы коордиитат
//    projection.setToIdentity();
//    float k = width() / (float)height();
//    projection.frustum(-10.1*k, 10.1, -10.1, 10.1, -10.2, 1000);

    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    //загржаем едиичнуую матрицу
    projection.setToIdentity();
    //утсанваливае перспетивную проэкцию
    projection.perspective(fov, aspect, zNear, zFar);

    updateGL();
}
//------------------------------------------------------------------------------
void MyGlWidget::paintGL()
{
    // очщаем буфферы
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QGLFunctions *f = context()->functions();

//    glEnable(GL_TEXTURE_2D);
//    f->glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, CurTexture);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotate);

    // выведем S-скан через стандартный шейдер
    //tex_ShaderProg.setUniformValue(0, CurTexture);
    tex_ShaderProg.setUniformValue("mvp_matrix", projection * matrix);

    drawCube();
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
    xRot = 1 / M_PI * (event->pos().y() - LastPoint.y());
    //yRot = 1 / M_PI * (event->pos().x() - LastPoint.x());
    QVector3D AxisX = QVector3D(1, 0, 0);
    rotate = QQuaternion::fromAxisAndAngle(AxisX, xRot);

    updateGL();
}
//------------------------------------------------------------------------------
//void MyGlWidget::mouseReleaseEvent(QMouseEvent *event)
//{

//}
//------------------------------------------------------------------------------
