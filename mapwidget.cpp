#include "mapwidget.h"
#include "qdebug.h"
#include "tpopoupwidget.h"
//------------------------------------------------------------------------------
const QString img_mark = ":/img/geometka.png";
//------------------------------------------------------------------------------
MapWidget::MapWidget(QWidget *parent) : QWidget(parent)
{
    SourceMapImage = NULL;
    ptList = NULL;

    SelectedPoint = -1;
    FindedPt = false;
    VisRect = QRect(1,1,1,1);
    mScale = 1;

    popupWidget = new TPopoupWidget(this);
    popupWidget->setWindowFlags(Qt::SplashScreen);
    popupWidget->setMinimumSize(QSize(200, 200));
    popupWidget->setVisible(false);

    setMouseTracking(true);
}
//------------------------------------------------------------------------------
MapWidget::~MapWidget()
{
    delete popupWidget;
}
//------------------------------------------------------------------------------
//обновим изображение
//------------------------------------------------------------------------------
void MapWidget::SetImage(QString image_name)
{
    if (SourceMapImage != NULL)
        delete SourceMapImage;

    SourceMapImage = new QImage(image_name);
    //инициализируем размер видимой области
    VisRect = SourceMapImage->rect();
    update();
}
//------------------------------------------------------------------------------
void MapWidget::SetPointsList( QList<TMapPoint>* ptr_list)
{
    //if (ptr_list != NULL)
   // QList<TMapPoint> *ptr;
    //ptr = ptr_list;
    ptList = ptr_list;

    //воздмонжо тут стоит вызваать обновление statck_widgeta
    //popup виджета с сооветсвие с текйшим набором точек
}
//------------------------------------------------------------------------------
//вывсечиавем popup-widget в уканнгой точки
//------------------------------------------------------------------------------
void MapWidget::ShowPopup(TMapPoint pt)
{
    FindedPt = true;

    //переовдим координты точек в координаты вджета
    QPoint m_point = QPoint((double)pt.p_pos.x() * ImgXKoff,
        (double)pt.p_pos.y() * ImgYKoff);

    m_point = QPoint(m_point.x() - popupWidget->width() / 2,
        m_point.y() - popupWidget->height());

    //обновим текущую точку
    popupWidget->setPoint(pt);
    popupWidget->setGeometry(QRect(mapToGlobal(m_point), popupWidget->size()));
    popupWidget->setVisible(true);    
}
//------------------------------------------------------------------------------
//обнолвяем пискмап текущего корпуса
//------------------------------------------------------------------------------
void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), Qt::gray);

    if (SourceMapImage != NULL) {
        //QRect target = rect, source = SourceMapImage->rect()
        painter.drawImage(rect(), *SourceMapImage, VisRect);
    }
        \
//    if ((SelectedPoint >= 0) && (ptList != NULL))
//    {
//        TMapPoint k_point =  ptList->at(SelectedPoint);

//        //рассчитаем коородинаты текущей активной точки
//        QPoint cur_point;
//        cur_point.setX(k_point.p_pos.x() * ImgXKoff);
//        cur_point.setY(k_point.p_pos.y() * ImgYKoff);

//        //отримуем метку
//        int mw = width() / 20, mh = height() /20;
//        QImage mark = QImage(img_mark).scaled(mw, mh);

//        //painter.drawImage(cur_point.x() - mw/2, cur_point.y() - mh, mark);
//        painter.drawImage(rect(), mark);
//        painter.setPen(Qt::black);
//        painter.drawText(cur_point.x(), cur_point.y() - mh -10, k_point.p_name);
//    }

    painter.end();
}
//------------------------------------------------------------------------------
void MapWidget::resizeEvent(QResizeEvent *event)
{
    event->accept();

    //расччитаыем коэффиценты
    ImgXKoff = (double)width() / VisRect.width();
    ImgYKoff = (double)height() / VisRect.height();

    //утснавоим размер всплывающего виджета
    popupWidget->setGeometry(0,0, width() / 10, height() / 10);

    update();
}
//------------------------------------------------------------------------------
//при нажаии на poup_widgert - отобразим gl_widget
//------------------------------------------------------------------------------
void MapWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    if (FindedPt)
    {
        FindedPt = false;
        return;
    }

    //определяем координату курсора отнисительно виджета с пискмапом
    QPoint clicked_pt = event->pos();
    //проверим, принадлежит - ли какой- либо точке выбранный пиксель
    QRect view_rect = QRect(clicked_pt.x(), clicked_pt.y(), 20, 20);

    int cur_point = -1;

//    for (int i = 0; i < ptList.length(); i++)
//    {
//        //переовдим координты точек в координаты вджета
//        QPoint m_point = QPoint((double)ptList.at(i).p_pos.x() * ImgXKoff,
//            (double)ptList.at(i).p_pos.y() * ImgYKoff);

//        //если курсор поапл в облатсь точки
//        if (view_rect.contains(m_point))
//        {
//            cur_point = i;
//            break;
//        }
//    }

//    popupWidget->setVisible(cur_point != -1);
//    if (popupWidget->isVisible())
//    {
//        popupWidget->setPoint(ptList.at(cur_point));
//        QSize w_size  = popupWidget->size();
//        QPoint w_point = QPoint(clicked_pt.x() - popupWidget->width() / 2,
//            clicked_pt.y() - popupWidget->height());

//        popupWidget->setGeometry(QRect(mapToGlobal(w_point), w_size));
//    }
}
//------------------------------------------------------------------------------
/*void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    if (FindedPt) return;

    //определяем координату курсора отнисительно виджета с пискмапом
    QPoint clicked_pt = event->pos();
    //проверим, принадлежит - ли какой- либо точке выбранный пиксель
    QRect view_rect = QRect(clicked_pt.x(), clicked_pt.y(), 20, 20);
    int cur_point = -1;

    for (int i = 0; i < ptList->length(); i++)
    {
        //переовдим координты точек в координаты вджета
        QPoint m_point = QPoint((double)ptList->at(i).map_point.x() * ImgXKoff,
            (double)ptList->at(i).map_point.y() * ImgYKoff);

        //если курсор поапл в облатсь точки
        if (view_rect.contains(m_point))
        {
            cur_point = i;
            break;
        }
    }

    popupWidget->setVisible(cur_point != -1);
    if (popupWidget->isVisible())
    {
        popupWidget->setPoint(CurrentMap->points.at(cur_point));
        QSize w_size  = popupWidget->size();
        QPoint w_point = QPoint(clicked_pt.x() - popupWidget->width() / 2,
            clicked_pt.y() - popupWidget->height());

        popupWidget->setGeometry(QRect(mapToGlobal(w_point), w_size));
    }
}*/
//------------------------------------------------------------------------------
//увеличиваем масштаб
//------------------------------------------------------------------------------
void MapWidget::wheelEvent(QWheelEvent *event)
{
    //определим масштаб
    double scale = event->angleDelta().y();
    scale = scale > 0 ? 0.01 : -0.01;
    mScale += scale;
    if (mScale < 0.01) mScale = 0.01;

    //устанвливаем точку приближения (координтаы видета переводим
    // в координты image)
    QPoint cl_point = event->pos();
    QPoint im_pt =  QPoint((double)cl_point.x() / ImgXKoff, (double)cl_point.y() / ImgYKoff);
    VisRect.moveCenter(im_pt);

    //шастабируем прямоугольгик просматриваемой олбасти карты
    VisRect.setWidth((double)width() * mScale);
    VisRect.setHeight((double)height() * mScale);

    qDebug() << "ww " << VisRect.width() << "hh " << VisRect.height();
    qDebug() << "sclae " << mScale;

    update();
}
//------------------------------------------------------------------------------
//при изменеие матсшаба измением размер видимой облатси изображения
//------------------------------------------------------------------------------
void MapWidget::Scale(QPoint pt, double scale)
{
    //устанвливаем точку приближения (координтаы видета переводим
    // в координты image)
    QPoint im_pt =  QPoint((double)pt.x() / ImgXKoff, (double)pt.y() / ImgYKoff);
    VisRect.moveCenter(im_pt);

    //шастабируем прямоугольгик просматриваемой олбасти карты
    VisRect.setWidth((double)width() * scale);
    VisRect.setHeight((double)VisRect.height() * scale);

    update();
}
