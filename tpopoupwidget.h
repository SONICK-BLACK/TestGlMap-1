#ifndef TPOPOUPWIDGET_H
#define TPOPOUPWIDGET_H

#include <QWidget>
#include <QPainter>
#include "vars.h"

class TPopoupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TPopoupWidget(QWidget *parent = nullptr);

    void setPoint(TMapPoint point) {CurPoint = point;}
    TMapPoint getPoint() {return CurPoint;}

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;


signals:
    void ShowPoint(TMapPoint point);

private:
    TMapPoint CurPoint;

public slots:
};

#endif // TPOPOUPWIDGET_H
