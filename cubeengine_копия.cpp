//#include "cubeengine.h"
////------------------------------------------------------------------------------
//struct VertexData
//{
//    QVector3D position;
//    QVector3D texCoord;
//};
////------------------------------------------------------------------------------
//CubeEngine::CubeEngine()
//    : indexBuf(QOpenGLBuffer::IndexBuffer)
//{
//    initializeOpenGLFunctions();

//    //при создание обьекта вылеим видеопамть по vbo
//    arrayBuf.create();
//    indexBuf.create();

//    initCubeGeometry();
//}
////------------------------------------------------------------------------------
//CubeEngine::~CubeEngine()
//{
//    arrayBuf.destroy();
//    indexBuf.destroy();
//}
////------------------------------------------------------------------------------
////инициализируем геметрию куба
////------------------------------------------------------------------------------
//void CubeEngine::initCubeGeometry()
//{
//    //заполяем  указываем вершинные и  текстурные координаты для каждой точки
//    VertexData vertices[] = {

//        //передняя грань
//        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
//        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
//        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
//        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

//        //правая грань
//        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
//        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
//        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
//        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

//        //задняя грань
//        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
//        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
//        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
//        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

//        //левая грань
//        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
//        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
//        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
//        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

//        //нижняя грань
//        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
//        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
//        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
//        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

//        //верзняя грань
//        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
//        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
//        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
//        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
//    };

////    // Индексы для рисования граней куба с помощью треугольников.
////    // Треугольники можно соединить дублированием индексов
////    // между полосками. Если соединительные полосы расположены противоположно
////    // порядок вершин, затем последний индекс первой полосы и первый
////    // индекс второй полоски необходимо продублировать. Если
////    // соединительные полосы имеют тот же порядок вершин, только последний
////    // индекс первой полосы необходимо продублировать.
////    GLushort indices[] = {
////         0,  1,  2,  3,  3,     // передняя грань 0 - triangle strip ( v0,  v1,  v2,  v3)
////         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
////         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
////        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
////        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
////        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
////    };

//    arrayBuf.bind();
//    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));
//}
////------------------------------------------------------------------------------
////процедура рисвания куба с кубичксокгй текстурой
////------------------------------------------------------------------------------
//void CubeEngine::drawCube(QGLShaderProgram *programm)
//{

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

//    //биндим VBO
//    arrayBuf.bind();
//    //indexBuf.bind();

//    //загрузим массив координат куба
//    quintptr offset = 0;

//    int vertexLocation = programm->attributeLocation("a_position");
//    programm->enableAttributeArray(vertexLocation);
//    programm->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//    //определяем текутурные координаты
//    offset += sizeof(QVector3D);

//    int texcoordLocation = programm->attributeLocation("a_texcoord");
//    programm->enableAttributeArray(texcoordLocation);
//    programm->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

//    //рисуем куб по массиву индексов, храняще муся в VBO1
//    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, indices);
//}
////------------------------------------------------------------------------------
