#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    LoadMapParams();

    ui->setupUi(this);
    ui->widget_Map->setMap(&CurrentMap);

    //ui->label_Korpus->setVisible(false);
    ui->openGLWidget->setVisible(true);
    ui->frame_Map->setVisible(false);
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
void MainWindow::LoadMapParams()
{
    QList<TMapPoint> kpoints = {
        {QString("BAZ"), QString(":/map1/pointA"), QPoint(3530, 3800), "svfgh", QString(":/map1/DSC_0200.JPG")},
        {QString("zzz"), QString(":/map1/pointB"), QPoint(3720, 3500), "sdggj", QString(":/map1/DSC_0201.JPG")},
        {QString("Lib"), QString(":/map1/pointC"), QPoint(2130, 3480), "dsfgg", QString(":/map1/DSC_0202.JPG")},
        {QString("Dk"), QString(":/map1/pointD"), QPoint(3180, 2850), "sfdf", QString(":/map1/DSC_0203.JPG")}
    };

    TMap Kampus = {
        kpoints,
        QString(":/img/campus_map_markless.png")
    };

    Maps.append(Kampus);

    QList<TMapPoint> gk1_points = {
        {QString("Вход А"), QString(":/map1/pointA"), QPoint(492, 474), "svfgh", QString(":/map_gl_fl1/p_ipt.JPG")},
        {QString("Njxrf .."), QString(":/map1/pointB"), QPoint(713, 121), "sdggj", QString(":/map_gl_fl1/p_smth.JPG")},
    };

    TMap gk1 = {
        gk1_points,
        QString(":/map_gl_fl1/map_gk_fl1.png")
    };
    Maps.append(gk1);

    TMap gk2 = {
        QList<TMapPoint>(),
        QString(":/map_gl_fl2/map_gk_2.png")
    };
    Maps.append(gk2);

    TMap gk3 = {
        QList<TMapPoint>(),
        QString(":/map_gl_fl1/map_gk_3.png")
    };
    Maps.append(gk3);

    CurrentMap = Maps.first();
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
//устанвливаем соответсующус списску карту
//------------------------------------------------------------------------------
void MainWindow::on_comboBox_activated(int index)
{
    CurrentMap = Maps.at(index);
    ui->widget_Map->setMap(&CurrentMap);
    ui->widget_Map->update();
}
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_Z_clicked()
{
}
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_m_clicked()
{

}
//------------------------------------------------------------------------------
//переходим в масштаб 1 к 1
//------------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    ui->widget_Map->mScale = 1;
    //ui->widget_Map->
}
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
