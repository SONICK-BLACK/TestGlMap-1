#include "tpopoupwidget.h"
#include "qdebug.h"
#include <QPaintEvent>
//------------------------------------------------------------------------------
TPopoupWidget::TPopoupWidget(QWidget *parent) : QWidget(parent)
{
}
//------------------------------------------------------------------------------
void TPopoupWidget::paintEvent(QPaintEvent *event)
{
    QRect img_rect = QRect(5, 10, width() - 5, height() * 2/3 - 5);
    QRect text_rect = QRect(5, img_rect.bottom() + 5, width() - 5, height() / 3);

    //отрисуем предварительно изображение точки
    QPainter painter;
    painter.begin(this);

    const QString fpath = ":/map1/pointС/main1.png";
    const QString img_mark = ":/img/geometka.png";

    QImage prev_img = QImage(fpath).scaled(img_rect.size());
    painter.drawImage(img_rect, prev_img);

    //отрисуем текст
    painter.setFont(QFont("Tahoma", 10));
    painter.drawText(text_rect, Qt::AlignCenter, CurPoint.p_name);
    painter.end();

    event->accept();
}
//------------------------------------------------------------------------------
void TPopoupWidget::resizeEvent(QResizeEvent *event)
{
    update();
}
//------------------------------------------------------------------------------
void TPopoupWidget::mousePressEvent(QMouseEvent *event)
{
    if (this->isVisible())
    {
        setVisible(false);
        ShowPoint(CurPoint);
    }

    event->accept();
}
//------------------------------------------------------------------------------
