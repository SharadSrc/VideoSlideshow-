#ifndef SLIDESHOWENGINE_H
#define SLIDESHOWENGINE_H

#include "sequencemodel.h"
#include "pixmap.h"
#include <QtGui>
#include "QVideoEncoder.h"


class slideShowEngine : public QWidget
{
    Q_OBJECT     

public:
    enum State {Paused=0x01, Running=0x02, Stopped=0x03,Finished=0x04};
    explicit slideShowEngine(QWidget *parent = 0);
    ~slideShowEngine();
    void setViewer(QGraphicsScene *scene) {m_scene=scene;};
    QGraphicsScene *viewer() {return m_scene;};
    void SetSequence(sequenceModel *sequence) {m_sequence=sequence;};
    int TotalTimeDuration(){return m_groupAnimation->duration();};
    int elapsedTime(){return m_groupAnimation->currentTime();};
    QAbstractAnimation::State state() {return m_groupAnimation->state();};
    void setExportMovie(QString movieName);
    void resetExportMovie();

signals:
    void finished();


protected:
    void timerEvent(QTimerEvent *event);

public slots:
    void animEnterFinished();
    void animDisplayFinished();
    void animExitFinished();

    void start();
    void pause();
    void resume();
    void stop();
    void setCurrentTime(int time);

private slots:
      void endOfSlideShow();


private:
    int m_timerId;
    QGraphicsScene *m_scene;
    sequenceModel *m_sequence;
    int m_currentSlideIndex;
    QList <Pixmap*> m_PixmapList;
    QSequentialAnimationGroup *m_groupAnimation;
    //QVideoEncoder encoder;
    bool m_exportToMovie;
    QString m_movieName;
    QSize m_size;

};

#endif // SLIDESHOWENGINE_H
