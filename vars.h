#ifndef VARS_H
#define VARS_H
//------------------------------------------------------------------------------
//Классы реализующие логику работы точкки и карты
//------------------------------------------------------------------------------
#include "windows.h"
#include <QObject>
#include <QRect>
//------------------------------------------------------------------------------
//структура интерактивной точки на карте
//------------------------------------------------------------------------------
//typedef struct
//{
    //название точки
//    QString p_name;
//    //назваение директории, хранящей текстуры
//    QString texture_name;

//    //координата точки в пискелях относительно карты
//    QPoint map_point;
//    //описание точки
//    QString p_decsr;
//    //название файла предпоказа точки
//    QString p_preview;


//    TMapPoint ()
//        : p_pos(), p_name(),
//        p_descript(), p_texFileName()
//    {}
//    TMapPoint (QPoint pos, QString name,
//        QString descr, QString texPath)
//    {
//        p_pos = pos;
//        p_name = name; p_descript = descr;
//        p_texFileName = texPath;
//    }
//} TMapPoint;
//------------------------------------------------------------------------------
class TMapPoint
{
public:
    //координат точки относительно bmp карты
    QString p_name;
    QPoint p_pos;
    QString p_descript;
    QString p_texFileName;

    TMapPoint ()
        : p_pos(), p_name(),
        p_descript(), p_texFileName()
    {}
    TMapPoint (const QString &name, QPoint pos,
        const QString &descr, const QString &texPath)
    {
        p_pos = pos;
        p_name = name; p_descript = descr;
        p_texFileName = texPath;
    }
};
//------------------------------------------------------------------------------
//класс списка точек
//------------------------------------------------------------------------------
typedef QList<TMapPoint> TPointList;
//class TPointList : public QList<TMapPoint>
//{
//public:
//    inline TPointList() Q_DECL_NOTHROW { }
//    inline explicit TPointList(const TMapPoint &i) { append(i); }
//    inline TPointList(const QList<TMapPoint> &l) : QList<TMapPoint>(l) { }

//    TPointList &operator=(const QList<TMapPoint> &other)
//    { QList<TMapPoint>::operator=(other); return *this; }

//    inline bool contains(const TMapPoint &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;

//    inline TPointList operator+(const TPointList &other) const
//    { TPointList n = *this; n += other; return n; }
//    inline TPointList &operator<<(const TMapPoint &str)
//    { append(str); return *this; }
//    inline TPointList &operator<<(const TPointList &l)
//    { *this += l; return *this; }
//    inline TPointList &operator<<(const QList<TMapPoint> &l)
//    { *this += l; return *this; }
//};
//------------------------------------------------------------------------------
//Параметры карты
//------------------------------------------------------------------------------
class TMap
{
public:
    //количчетво слоев карты
    int layersCount;
    int curLayer;

    QStringList images;
    //список точек по слоям
    QList<TPointList> l_points;

    TMap ()
        : layersCount(), curLayer(),
          images(), l_points()
    {}

    TMap (int l_count, QStringList img, QList<TPointList> l_pt)
    {
        layersCount = l_count;
        curLayer = 0;
        images = img;
        l_points = l_pt;
    }
};
//------------------------------------------------------------------------------
#endif // VARS_H
