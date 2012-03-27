#include <QtGui>
#include "const.h"
#include "node.h"

node::node()
{
    setPixmapSize(QSize(PREVIEW_WIDTH,PREVIEW_HEIGHT));
    setIconSize(QSize(ICON_WIDTH,ICON_HEIGTH));
    setNodeName("---");
}


node::~node()
{    


}

 void node::setNodePixmap(QPixmap pixmap)
 {
     if(pixmap.width()>m_pixmapSize.width() || pixmap.height()>m_pixmapSize.height())
        m_nodePixmap=pixmap.scaled(m_pixmapSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
     else
         m_nodePixmap=pixmap;     
 }


QPixmap node::nodeIcon()
{
QPixmap iconized;

    iconized=m_nodePixmap.scaled(m_iconSize,Qt::KeepAspectRatio,Qt::FastTransformation);
    return iconized;
}


void node::setEnterAnimation(QPropertyAnimation *animation, Pixmap *item)
{
    animation->setTargetObject(item);
    animation->setPropertyName(enterEffect().effectType().toAscii());
    animation->setDirection(enterEffect().direction());
    animation->setDuration(enterEffect().duration());

    if(enterEffect().effectType()=="pos")
    {
        animation->setStartValue(enterEffect().startPointF());
        animation->setEndValue(enterEffect().endPointF());
    }
    else
    {
        animation->setStartValue(enterEffect().startValue());
        animation->setEndValue(enterEffect().endValue());
    }    
    animation->setEasingCurve(enterEffect().easingCurve());
}



void node::setDisplayAnimation(QPropertyAnimation *animation, Pixmap *item)
{
    animation->setTargetObject(item);
    animation->setPropertyName(displayEffect().effectType().toAscii());

    animation->setDirection(displayEffect().direction());
    animation->setDuration(displayEffect().duration());

    if(displayEffect().effectType()=="pos")
    {
        animation->setStartValue(displayEffect().startPointF());
        animation->setEndValue(displayEffect().endPointF());
    }
    else
    {
        animation->setStartValue(displayEffect().startValue());
        animation->setEndValue(displayEffect().endValue());
    }
    animation->setEasingCurve(displayEffect().easingCurve());
}


void node::setExitAnimation(QPropertyAnimation *animation, Pixmap *item)
{
    animation->setTargetObject(item);
    animation->setPropertyName(exitEffect().effectType().toAscii());

    animation->setDirection(exitEffect().direction());
    animation->setDuration(exitEffect().duration());

    if(exitEffect().effectType()=="pos")
    {
        animation->setStartValue(exitEffect().startPointF());
        animation->setEndValue(exitEffect().endPointF());
    }
    else
    {
        animation->setStartValue(exitEffect().startValue());
        animation->setEndValue(exitEffect().endValue());
    }
    animation->setEasingCurve(exitEffect().easingCurve());
}


// Paolo: dava errore con const &effectData ora non più. Perchè?
QDataStream &operator<<(QDataStream &out, node &nodeData)
{

    out << nodeData.nodePath() << nodeData.nodePixmap() << nodeData.nodeName();
    out << nodeData.iconSize() << nodeData.pixmapSize();
    effect enE=nodeData.enterEffect();
    effect dE=nodeData.displayEffect();
    effect exE=nodeData.exitEffect();
    out << enE << dE << exE;
    return out;
}

QDataStream &operator>>(QDataStream &in, node &nodeData)
{

    QString nodePath,nodeName;
    QPixmap nodePixmap;
    QSize iconSize,pixmapSize;
    effect enterEffect,displayEffect,exitEffect;


    in >> nodePath >> nodePixmap >> nodeName;
    in >> iconSize >> pixmapSize;
    in >> enterEffect >> displayEffect >> exitEffect;


    nodeData.setNodePath(nodePath);
    nodeData.setNodePixmap(nodePixmap);
    nodeData.setNodeName(nodeName);
    nodeData.setIconSize(iconSize);
    nodeData.setPixmapSize(pixmapSize);
    nodeData.setEnterEffect(enterEffect);
    nodeData.setDisplayEffect(displayEffect);
    nodeData.setExitEffect(exitEffect);

    return in;
}

