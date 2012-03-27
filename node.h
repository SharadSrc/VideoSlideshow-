#ifndef NODE_H
#define NODE_H

#include "effect.h"
#include "pixmap.h"
#include <QString>
#include <QPixmap>
#include <QMetaType>
#include <QPropertyAnimation>



class node
{

public:
    //enum resolution { R320x240,R640x480,R800x600,R1027x768,R1280x1024,R1600x1200,RNULL};
    node();
    ~node();
    void setNodePath(QString path) {m_nodePath=path;};
    QString nodePath() {return m_nodePath;};
    void setNodePixmap(QPixmap pixmap);
    QPixmap nodePixmap() {return m_nodePixmap;};
    void setNodeName(QString name) {m_nodeName=name;};
    QString nodeName(){return m_nodeName;};
    QPixmap nodeIcon();
    void setIconSize(QSize size) {m_iconSize=size;};
    QSize iconSize() {return m_iconSize;};
    void setPixmapSize(QSize size) {m_pixmapSize=size;};
    QSize pixmapSize() {return m_pixmapSize;};

    void setEnterEffect (effect enterEffect) {m_enterEffect=enterEffect;};
    void setDisplayEffect (effect displayEffect) {m_displayEffect=displayEffect;};
    void setExitEffect (effect exitEffect) {m_exitEffect=exitEffect;};

    effect enterEffect() {return m_enterEffect;};
    effect displayEffect() {return m_displayEffect;};
    effect exitEffect() {return m_exitEffect;};

    void setEnterAnimation(QPropertyAnimation *animation, Pixmap *item);
    void setDisplayAnimation(QPropertyAnimation *animation, Pixmap *item);
    void setExitAnimation(QPropertyAnimation *animation, Pixmap *item);

    //void copyNode( node*);


private:
    QString m_nodePath,m_nodeName;
    QPixmap m_nodePixmap;
    QSize m_iconSize,m_pixmapSize;
    effect m_enterEffect,m_displayEffect,m_exitEffect;


};


QDataStream &operator<<(QDataStream &out,node &effectData);
QDataStream &operator>>(QDataStream &in, node &effectData);


Q_DECLARE_METATYPE(node)
#endif // NODE_H



