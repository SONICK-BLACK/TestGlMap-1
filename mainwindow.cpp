#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QStackedWidget>
#include "mapwidget.h"
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Maps.clear();
    LoadMapParams();

    ui->setupUi(this);
    //ui->widget_Map->setMap(&CurrentMap);

    //ui->label_Korpus->setVisible(false);
    ui->openGLWidget->setVisible(false);
    //ui->frame_Map->setVisible(true);
    //ui->label_Korpus->setScaledContents(true);
    //ui->stackedWidget_Map->addWidget(new QWidget(this));


    //connect(ui->widget_Map, SIGNAL(ShowPoint(int)), this, SLOT(ShowPoint(int)));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(setCurrentMap(int)));

    //connect(ui->widget_Map->popupWidget, SIGNAL(ShowPoint(TMapPoint)), this, SLOT(ShowPoint(TMapPoint)));
//    connect(ui->pushButton_Search, SIGNAL(clicked(bool)), this, SLOT(FindPoint(QString&)))
    connect(ui->lineEdit_search, SIGNAL(textChanged(QString)), this, SLOT(FindPoint(QString)));

    setCurrentMap(0);
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
    TPointList kpoints = {
        TMapPoint("BAZ",  QPoint(3530, 3800), "svfgh", ":/map1/pointA"),
        TMapPoint("zzz", QPoint(3720, 3500), "sdggj",  ":/map1/pointB"),
        TMapPoint("Lib", QPoint(2130, 3480), "dsfgg",  ":/map1/pointC"),
        TMapPoint("Dk", QPoint(3180, 2850), "sfdf",    ":/map1/pointD")
    };

    QList<TPointList> p_lst =  {kpoints};
    QStringList n_lst = {QString(":/map1/campus_map.png")};

    TMap Kampus(1, n_lst, p_lst);
    Maps.append(Kampus);
    qDebug() << "lampus " << Kampus.images.first();


    TPointList gk1_points = {
        TMapPoint("Вход А",  QPoint(492, 474), "svfgh", ":/map1/pointA"),
        TMapPoint("data1 ..", QPoint(713, 121), "sdggj", ":/map1/pointB")
    };

    TPointList gk2_points = {
        TMapPoint("Вход B",  QPoint(492, 474), "svfgh", ":/map1/pointA"),
        TMapPoint("data2 ..", QPoint(713, 121), "sdggj", ":/map1/pointB")
    };

    TPointList gk3_points = {
        TMapPoint("Вход C", QPoint(492, 474), "svfgh", ":/map1/pointA"),
        TMapPoint("data3 ..", QPoint(713, 121), "sdggj", ":/map1/pointB")
    };

    TPointList gk4_points = {
        TMapPoint("Вход В", QPoint(492, 474), "svfgh", ":/map1/pointA"),
        TMapPoint("data4 ..", QPoint(713, 121), "sdggj", ":/map1/pointB")
    };

    QStringList layers= {
        QString(":/map_gl_fl1/map_gk_fl1.png"),  QString(":/map_gl_fl2/map_gk_2.png"),
        QString(":/map_gl_fl3/map_gk_3.png"), QString(":/map_gl_fl4/map_gk_4.png")
    };

    QList<TPointList> lay_points = {gk1_points, gk2_points, gk3_points, gk4_points};

    TMap map_gk(4, layers, lay_points);
    Maps.append(map_gk);
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
//    bool have_pt = false;
//    //прореям совпдениеимени среди всех точек на катре
//    TMapPoint pt;
//    qDebug() << "p_anem " << point_name;
//    foreach (int p = 0; p < )
//    {
//        qDebug() << "pt " << pt.p_name;
//        if (pt.p_name == point_name)
//        {
//            have_pt = true;
//            break;
//        }
//    }

//    if (have_pt)
//    {
//        ui->widget_Map->ShowPopup(pt);
//    }
}
//-----------------------------------------------------------------------------
//обновляем текущую карту
//-----------------------------------------------------------------------------
void MainWindow::setCurrentMap(int index)
{
    CurrentMap =  Maps.at(index);
    //изменим размер списка элементов
    int sz = ui->stackedWidget_Map->count();
    qDebug() << "sz " << sz << "l " << CurrentMap.layersCount;

    //удаляем элменты
    if (CurrentMap.layersCount < sz)
    {
        for (int w = 0; w < sz - CurrentMap.layersCount; w++)
        {
            QWidget *widget = ui->stackedWidget_Map->widget(w);
            //удаляем из списка
            ui->stackedWidget_Map->removeWidget(widget);

            //удяаляем обьект виджета из памаяти
            MapWidget *lay_widget = static_cast<MapWidget*>(widget);
            delete lay_widget;
        }
    }
    //добавляем элменты
    else
    {
        for (int w = 0;  w < CurrentMap.layersCount - sz;  w++)
            ui->stackedWidget_Map->addWidget(new MapWidget(this));
    }


    //обновляем все элменты stack_widget
    for (int l = 0; l < CurrentMap.layersCount; l++)
    {
        MapWidget *lay_widget = static_cast<MapWidget*>(ui->stackedWidget_Map->widget(l));
        lay_widget->SetImage(CurrentMap.images.at(l));

        qDebug() << "laver " << l;

//        TPointList *pt_lst = static_cast<TPointList*>(&CurrentMap.l_points.at(l));
//        lay_widget->SetPointsList(pt_lst);
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_toolButton_return_clicked()
{
    ui->openGLWidget->setVisible(false);
    ui->frame_Map->setVisible(true);
}
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
