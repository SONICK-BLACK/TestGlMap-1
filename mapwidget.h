#ifndef MAPWIDGET_H
#define MAPWIDGET_H
//------------------------------------------------------------------------------
//виджет для отрисовки map-ов
//------------------------------------------------------------------------------
#include <QWidget>
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
//------------------------------------------------------------------------------
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget *parent = nullptr);

    void setMap(TMap *map);

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private :
    TMap *CurrentMap;
    QImage *SourceMapImage;
    //полигон метки
    QPolygon mark_poly;

    //коэффиценты отношения размеров
    //исходного QImage к размерам виджета
    double ImgXKoff;
    double ImgYKoff;

    //кооридинаты последнего нажатия мышой
    QPoint LastClickedPt;
    //индекс выбранной точки в спсиске текущйе карты
    int SelectedPoint;

signals:
    //сигнал, излчаемый при нажатии на точку
    void ShowPoint(int SelectedPoint);

public slots:
};

#endif // MAPWIDGET_H
