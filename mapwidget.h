#ifndef MAPWIDGET_H
#define MAPWIDGET_H
//------------------------------------------------------------------------------
//виджет для отрисовки слоя
//------------------------------------------------------------------------------
#include <QWidget>
#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFrame>
#include "tpopoupwidget.h"
//------------------------------------------------------------------------------
class MapWidget : public QWidget
{
    Q_OBJECT
public:
    //всплывающий при наведении на элемент фрейм
    TPopoupWidget *popupWidget;
    double mScale;

    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

    void SetImage(QString image_name);
    void SetPointsList(const  QList<TMapPoint> &ptr_list);

//    TPointList GetPointsList() const;
//    QImage GetImage() const;

    void ShowPopup(TMapPoint pt);

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private :
    QImage *SourceMapImage;
    TPointList *ptList;

    //полигон метки
    QPolygon mark_poly;
    //прямоугольнник отрисовываемоого учатска карыт
    QRect VisRect;

    //елси флаг поднят - занчит тока активаироавнна поиском
    //сброс т возжмене тоьлок при надатии мыши
    bool FindedPt;

    //коэффиценты отношения размеров  исходного QImage к размерам виджета
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
    void Scale(QPoint pt, double scale);
};

#endif // MAPWIDGET_H
