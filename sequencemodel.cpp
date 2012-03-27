#include <QtGui>
#include "node.h"
#include "sequencemodel.h"


#define FILE_VERSION "0.2"

sequenceModel::sequenceModel(QObject *parent)
        : QAbstractListModel(parent)
{
    m_modified=false;
    m_movieResolution=QSize(640,480);
    m_bitRate=1000000;
    m_frameRate=25;
}

int sequenceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_sequence.size();
}


QVariant sequenceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    node item;
    item=m_sequence.at(index.row());
    QPixmap icon=item.nodeIcon();
    QPixmap pix=item.nodePixmap();
    QString name=item.nodeName();

    if (role == Qt::DecorationRole)
        return QVariant(icon);

    if(role == Qt::DisplayRole)
    {
        return QVariant(name);
    }

    if(role == Qt::UserRole)
    {
        QVariant v;
        v.setValue(item);
        return v;
    }
    else
        return QVariant();

}


Qt::ItemFlags sequenceModel::flags(const QModelIndex &index)
{
    Qt::ItemFlags theFlags= QAbstractListModel::flags(index);

    if (index.isValid())
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEditable| Qt::ItemIsEnabled;
    return theFlags;

}


bool sequenceModel::setData (const QModelIndex &index, const QVariant &value, int role)
{

    if (index.isValid() && role == Qt::EditRole)
    {
        node item = value.value<node>();
        int i=index.row();
        m_sequence.replace(i,item);
        setModified(true);
        emit dataChanged(index, index);
        return true;
    }
    else
        return false;
}



bool sequenceModel::appendRow (const QVariant &value, int role)
{

    if (role == Qt::EditRole)
    {
        QModelIndex i;
        int row=rowCount();
        insertRow(row,QModelIndex());
        i=index(row);
        setData(i,value,Qt::EditRole);        
        return true;
    }
    else
        return false;
}



bool sequenceModel::insertRow (int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row +1);
    node item;
    m_sequence.append(item);
    setModified(true);
    endInsertRows();
    return true;


}


bool sequenceModel::removeRow (int row, const QModelIndex & parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + 1);    
    m_sequence.removeAt(row);
    setModified(true);
    endRemoveRows();
    return true;

}

void sequenceModel::load(const QString &filename)
{
quint32 myId;

    // queste sono operazioni lunghe... ci vuole una progress bar

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << tr("cannot open file for reading: ")  << qPrintable(file.errorString()) << endl;
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_7);

    in >> myId;

    if(myId!= 0x12345678)
    {
        qDebug() << tr("openSequenceFile: my Id wrong");
        return;
    }

    QString fileVersion;

    in >> fileVersion;

    if (fileVersion!=FILE_VERSION)
    {
        QMessageBox msgBox;
        QString str=QString(tr("File not valid!\nVersion: "));
        str.append(fileVersion);
        msgBox.setText(str);
        msgBox.exec();
        return;
    }


    in >> m_audioTracks;


    //QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

     //in >> str >> m_projectPath >> m_titleFirstLine >> m_titleSecondLine >> m_author >> m_date >> res;
     int i=0;
     while(!file.atEnd())
     {
         node nodeItem;
         in >> nodeItem;
         QVariant v;
         v.setValue(nodeItem);
         appendRow(v);
         i++;
     }
     setModified(false);
     //QApplication::restoreOverrideCursor();
}

void sequenceModel::save(const QString &filename)
{
    // queste sono operazioni lunghe... ci vuole una progress bar

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << tr("cannot open file for writing: ")  << qPrintable(file.errorString()) << endl;
        return;
    }


    //QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_7);
    out << quint32(0x12345678);

    out << QString(FILE_VERSION);

    out << m_audioTracks;

    //out << objectName() << m_projectPath << m_titleFirstLine << m_titleSecondLine << m_author << m_date << res;

    for(int i=0; i<m_sequence.size(); i++)
    {
        node item = m_sequence.at(i);
        out << item;

    }

    file.close();
    setModified(false);
    //QApplication::restoreOverrideCursor();
}



void sequenceModel::clear()
{

    // usa la clear della lista e invalida tutto il modello...

    m_sequence.clear();
    reset();
    /*int t=rowCount();
    for(int i=0; i<t;i++)
        removeRow(0);*/
    setModified(false);
}



int sequenceModel::duration()
{
    node itemNode;
    int totalTime=0;

    for(int i=0; i<rowCount();i++)
    {
        itemNode=m_sequence.at(i);
        totalTime+=itemNode.enterEffect().duration();
        totalTime+=itemNode.displayEffect().duration();
        totalTime+=itemNode.exitEffect().duration();

    }
    return totalTime;
}


/*
QString sequenceModel::durationStdTime()
{
QString stdTime;

    int msDuration=duration();
    int cent=msDuration/10;
    int seconds=msDuration/1000;
    int minutes=seconds/60;
    int hour=minutes/60;

    stdTime=QString("%1 : %1 : %1.%1").arg(hour,minutes,seconds,cent);

    return stdTime;
}*/

