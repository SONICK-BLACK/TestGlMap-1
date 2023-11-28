#ifndef VARS_H
#define VARS_H
//------------------------------------------------------------------------------
#include "windows.h"
#include <QObject>
#include <QRect>
//------------------------------------------------------------------------------
//структура интерактивной точки на карте
//------------------------------------------------------------------------------
typedef struct
{
    //название точки
    QString p_name;
    //назваение директории, хранящей текстуры
    QString texture_name;

    //координата точки в пискелях относительно карты
    QPoint map_point;
    //описание точки
    QString p_decsr;
    //название файла предпоказа точки
    QString p_preview;


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
#endif // VARS_H
