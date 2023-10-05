#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    LoadBuildParams();

    ui->setupUi(this);
    ui->widget_Map->setMap(&CurrentMap);

    ui->label_Korpus->setVisible(false);
    ui->openGLWidget->setVisible(false);
    ui->widget_Map->setVisible(true);
    //ui->label_Korpus->setScaledContents(true);


    connect(ui->widget_Map, SIGNAL(ShowPoint(int)), this, SLOT(ShowPoint(int)));
}
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------
//загружаем парматеры карты
//------------------------------------------------------------------------------
void MainWindow::LoadBuildParams()
{
    QList<TMapPoint> kpoints = {
        {QString("BAZ"), QString(":/map1/pointA"), QPoint(3530, 3800)},
        {QString("zzz"), QString(":/map1/pointB"), QPoint(3720, 3500)},
        {QString("Lib "), QString(":/map1/pointC"), QPoint(2130, 3480)}
    };

    CurrentMap = {
        kpoints,
        QString(":/img/campus_map_markless.png")
    };

}
//------------------------------------------------------------------------------
//выводим кубмап выбранной точки
//------------------------------------------------------------------------------
void MainWindow::ShowPoint(int point)
{
    qDebug() << "poit " << point;

    //загрузим текстуру тоекущей точки (метки) в графический движок
    ui->openGLWidget->LoadCubeTexture(CurrentMap.points.at(point).texture_name);
    // спрячем виджет  карты
    ui->widget_Map->setVisible(false);
    ui->openGLWidget->setVisible(true);

}
//------------------------------------------------------------------------------
void MainWindow::on_toolButton_return_clicked()
{
    ui->openGLWidget->setVisible(false);
    ui->widget_Map->setVisible(true);
}
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{

}
//------------------------------------------------------------------------------
void MainWindow::resizeEvent(QResizeEvent *event)
{
}
//------------------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent *event)
{
}
//------------------------------------------------------------------------------
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
}
