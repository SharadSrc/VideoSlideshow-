#include <QtGui>
#include "node.h"
#include "delegate.h"



 delegate::delegate(QWidget *parent)
     : QStyledItemDelegate(parent)
 {

 }

void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    node item;

     if (qVariantCanConvert<QPixmap>(index.data(Qt::DecorationRole)))
     {
        QVariant val=index.data(Qt::UserRole);
        item=val.value<node>();

        QPixmap pix=item.nodeIcon();
        int offsetV = 0;

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
            //painter->setPen(Qt::blue);
            //painter->drawRect(option.rect);
        }

        painter->drawPixmap(option.rect.x(),offsetV+option.rect.y(),pix.width(),pix.height(),pix);
     }
     else
     {
         QStyledItemDelegate::paint(painter, option, index);
     }

}


QSize delegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (qVariantCanConvert<QPixmap>(index.data(Qt::DecorationRole)))
    {
        QVariant val=index.data(Qt::DecorationRole);
        QPixmap pix=val.value<QPixmap>();

        return QSize(pix.width()*3/2,pix.height());
    }
    else
        return QStyledItemDelegate::sizeHint(option, index);
}


QWidget *delegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const

{
    return QStyledItemDelegate::createEditor(parent, option, index);

}


void delegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}



void delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{

    QStyledItemDelegate::setModelData(editor, model, index);
}


void delegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
