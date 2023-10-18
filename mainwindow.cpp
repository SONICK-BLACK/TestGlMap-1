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
    ui->frame_Map->setVisible(true);
    //ui->label_Korpus->setScaledContents(true);


    //connect(ui->widget_Map, SIGNAL(ShowPoint(int)), this, SLOT(ShowPoint(int)));
    connect(ui->widget_Map->popupWidget, SIGNAL(ShowPoint(TMapPoint)), this, SLOT(ShowPoint(TMapPoint)));
//    connect(ui->pushButton_Search, SIGNAL(clicked(bool)), this, SLOT(FindPoint(QString&)))
    connect(ui->lineEdit_search, SIGNAL(textChanged(QString)), this, SLOT(FindPoint(QString)));
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
        {QString("BAZ"), QString(":/map1/pointA"), QPoint(3530, 3800), "svfgh"},
        {QString("zzz"), QString(":/map1/pointB"), QPoint(3720, 3500), "sdggj"},
        {QString("Lib"), QString(":/map1/pointC"), QPoint(2130, 3480), "dsfgg"},
        {QString("Dk"), QString(":/map1/pointD"), QPoint(3180, 2850), "sfdf"}
    };

    CurrentMap = {
        kpoints,
        QString(":/img/campus_map_markless.png")
    };

}
//------------------------------------------------------------------------------
//выводим кубмап выбранной точки
//------------------------------------------------------------------------------
void MainWindow::ShowPoint(TMapPoint point)
{
    //загрузим текстуру тоекущей точки (метки) в графический движок
    ui->openGLWidget->LoadCubeTexture();
    // спрячем виджет  карты
    ui->frame_Map->setVisible(false);
    ui->openGLWidget->setVisible(true);

}
//-----------------------------------------------------------------------------
void MainWindow::FindPoint(QString point_name)
{
    bool have_pt = false;
    //прореям совпдениеимени среди всех точек на катре
    TMapPoint pt;
    qDebug() << "p_anem " << point_name;
    foreach (pt, CurrentMap.points)
    {
        qDebug() << "pt " << pt.p_name;
        if (pt.p_name == point_name)
        {
            have_pt = true;
            break;
        }
    }

    if (have_pt)
    {
        ui->widget_Map->ShowPopup(pt);
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_toolButton_return_clicked()
{
    ui->openGLWidget->setVisible(false);
    ui->frame_Map->setVisible(true);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_Search_clicked()
{
    QString pt_name = ui->lineEdit_search->text();
    FindPoint(pt_name);
}
//------------------------------------------------------------------------------
//выосетим тескеит посика
//------------------------------------------------------------------------------
void MainWindow::on_toolButton_Search_clicked(bool checked)
{
    ui->lineEdit_search->setVisible(checked);
    ui->pushButton_Search->setVisible(checked);
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
