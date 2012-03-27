#ifndef SLIDESHOWENGINE_H
#define SLIDESHOWENGINE_H

#include "node.h"
#include "sequencemodel.h"
#include "pixmap.h"
#include <QtGui>



#define TIMER_ANIMATION 5    // slide show refresh time (animations...)

class slideShowEngine : public QWidget
{
    Q_OBJECT

    enum Step {EnterAnimation=0x01,DisplayAnimation=0x02,ExitAnimation=0x03};
    enum AnimationState {RunningAnimation=0x01,EndAnimation=0x02};


public:

    enum State {Paused=0x01, Running=0x02, Stopped=0x03,Finished=0x04};

    explicit slideShowEngine(QWidget *parent = 0);
    ~slideShowEngine();
    void setViewer(QGraphicsScene *scene) {m_scene=scene;};
    QGraphicsScene *viewer() {return m_scene;};
    void setSequence(sequenceModel *sequence) {m_sequence=sequence;};
    //int totalTimeDuration();
    int elapsedTime(){return m_totalCurrentTime;};
    State state() {return m_currentState;};
    void setExportMovie(QString movieName);
    bool exportToMovie() {return m_exportToMovie;};
    void resetExportMovie();
    void setViewerSize(QSize size){m_size=size;};
    QSize viewerSize(){return m_size;};

    //void setMovieBitRate(int bitRate) {m_bitRate=bitRate;};
    //int movieBitRate() {return m_bitRate;};
    //void setMovieFrameRate(int frameRate) {m_frameRate=frameRate;};
    //int movieFrameRate() {return m_frameRate;};

signals:
    void finished();
    void refresh(int);


protected:
    void timerEvent(QTimerEvent *event);


public slots:
    //void animEnterFinished();
    //void animDisplayFinished();
    //void animExitFinished();

    void start();
    void pause();
    void resume();
    void stop();    
    void setCurrentTime(int time);    

private slots:
      void endOfSlideShow();


private:

    void startSound();
    void pauseSound();
    void resumeSound();
    void stopSound();
    void setState(State newState){m_currentState=newState;};
    Step step()  {return m_currentStep;};
    void setStep(Step newStep){m_currentStep=newStep;};
    AnimationState applyAnimation();
    State runEngine();

    int m_timerId;
    QGraphicsScene *m_scene;
    sequenceModel *m_sequence;
    int m_currentSlideIndex;
    QList <Pixmap*> m_PixmapList;
    //QSequentialAnimationGroup *m_groupAnimation;
    //QVideoEncoder encoder;
    State m_currentState;
    Step m_currentStep;
    node m_currentNode;
    int m_totalCurrentTime;
    int m_stepCurrentTime;
    bool m_exportToMovie;
    QString m_movieName;
    QTime m_timerAnimation;
    QSize m_size;
    //int m_bitRate;
    //int m_frameRate;
    //QVideoEncoder encoder;
    //int storeTimerAnimation;
    //QTime m_totalTime;
    //int storeTotalTime;
    unsigned int m_frame_number;

    QProcess m_ffmpegProcess;
    QProcess m_mplayerProcess;


};





class ImageLoader : public QThread {
Q_OBJECT
public:

    ImageLoader()
        : QThread()
    {
        m_go=false;
        m_size=QSize(640,480);
    }

    void run()
    {
        int index=0;
        while(true)
        {
            QTime time;
            if(m_go)
            {
             time.start();
             bool res=m_img->load("/home/paolo/Pictures/Photos/cover.png");
             if(m_img->width()>m_size.width() || m_img->height()>m_size.height())
                 *m_img=m_img->scaled(m_size,Qt::KeepAspectRatio,Qt::SmoothTransformation);

             int elapsed=time.elapsed();
             qDebug() << "thread run " << index << "elapsed=" << elapsed << res;
             index++;
             m_go=false;
            }

            yieldCurrentThread();
        }
    }

public slots:


    void go(QString path, QImage *img)
    {
        m_imgPath=path;
        m_img=img;
        m_go=true;
    }


    void setResolution(QSize res)
    {
        m_size=res;
    }



private:
    bool m_go;
    QImage *m_img;
    QSize m_size;
    QString m_imgPath;

};






#endif // SLIDESHOWENGINE_H
