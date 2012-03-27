#ifndef SEQUENCEMODEL_H
#define SEQUENCEMODEL_H


#include <QAbstractListModel>
#include <QList>
#include "node.h"


class sequenceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    sequenceModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index);
    bool appendRow (const QVariant &value, int role = Qt::EditRole);
    bool insertRow (int row, const QModelIndex &parent = QModelIndex());
    bool removeRow (int row, const QModelIndex & parent = QModelIndex());
    void clear();

    void load(const QString &filename);
    void save(const QString &filename);
    void setModified(bool state) {m_modified=state;};
    bool isModified(){return m_modified;};

    void setMovieResolution(QSize size) {m_movieResolution=size;};
    QSize movieResolution() {return m_movieResolution;};
    void setMovieBitRate(int bitRate) {m_bitRate=bitRate;};
    int movieBitRate() {return m_bitRate;};
    void setMovieFrameRate(int frameRate) {m_frameRate=frameRate;};
    int movieFrameRate() {return m_frameRate;};
    void addSoundtrack(QString track) {m_audioTracks.append(track);m_modified=true;};
    void removeSoundtrack(int i){m_audioTracks.removeAt(i);m_modified=true;};
    QStringList soundtracks() {return m_audioTracks;};
    void swapSoundtrack(int i, int j){m_audioTracks.swap(i,j);m_modified=true;};
    //int slidesCount(){return m_sequence.count();};
    //int slideShowDuration();
    //void setSlideShowDuration(int duration);
    int duration();
    //QString durationStdTime();

private:
    int m;
    QList <node> m_sequence;
    bool m_modified;
    QSize m_movieResolution; //-s  WxH
    int m_bitRate;   // -b
    int m_frameRate; // -r
    QStringList m_audioTracks;
};





#endif // SEQUENCEMODEL_H
