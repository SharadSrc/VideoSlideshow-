#ifndef PIXMAP_H
#define PIXMAP_H

#include <QPixmap>
#include <QPointF>
#include <QGraphicsPixmapItem>

class Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    //Q_PROPERTY(QGraphicsEffect graphicsEffect READ graphicsEffect WRITE setGraphicsEffect)

public:
    Pixmap(const QPixmap &pix)
        : QObject(), QGraphicsPixmapItem(pix)
    {
        //setCacheMode(ItemCoordinateCache);
        //setTransformationMode(Qt::SmoothTransformation);
        setTransformationMode(Qt::FastTransformation);
    }
};



#endif // PIXMAP_H
