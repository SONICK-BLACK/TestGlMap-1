#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//------------------------------------------------------------------------------
//основное окно, отрисовываем крату кампуса, с помощью которой можно выбарть
// корппус, при наличии выбранного корпуса, отрисуем схему (вид  сверзу)
//------------------------------------------------------------------------------
#include <QMainWindow>
//#include "vars.h"
//------------------------------------------------------------------------------
//структура интерактивной точки на карте
//------------------------------------------------------------------------------
typedef struct
{
    //название (и описание ) точки
    QString p_name;
    //назваение директории, хранящей текстуры
    QString texture_name;
    //координата точки в пискелях относительно карты
    QPoint map_point;

} TMapPoint;
//------------------------------------------------------------------------------
//Параметры карты
//------------------------------------------------------------------------------
typedef struct
{
    //список точек
    QList<TMapPoint> points;
    //изобраежеиение караты
    QString image;

} TMap;
//------------------------------------------------------------------------------
namespace Ui {
class MainWindow;
}
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    TMap CurrentMap;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void LoadBuildParams();

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_pushButton_clicked();
    void ShowPoint(int point);

    void on_toolButton_return_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
