#include "mainwindow.h"
#include "slideshowengine.h"

slideShowEngine::slideShowEngine(QWidget *parent) :
    QWidget(parent)
{
    m_currentSlideIndex=0;
    m_currentState=Stopped;
    m_exportToMovie=false;
    m_totalCurrentTime=0;
    m_frame_number=0;
    //m_groupAnimation = new QSequentialAnimationGroup;
}

slideShowEngine::~slideShowEngine()
{

    //m_groupAnimation->clear(); // basta anche per le animazioni parallele?
    // scan m_groupAnimation and delete all the animations
    /*for(int i=0; i<m_PixmapList.size()-1;i++)
    {
       Pixmap *item = m_PixmapList[i];
       delete item;
    }*/

    m_PixmapList.clear();
    //delete m_groupAnimation;

}

void slideShowEngine::setCurrentTime(int time)
{
    Q_UNUSED(time);
    //if(time>m_groupAnimation->currentTime()) // no backward direction
        //m_groupAnimation->setCurrentTime(time);
   // qDebug() << "not yet implemented: some problem to fix...";
}





slideShowEngine::State slideShowEngine::runEngine()
{
int ret,x,y;
QPixmap pix;
QModelIndex index;
QVariant val;
node itemNode;
Pixmap *item;
effect e;


    if(m_currentState!=Running)
        return m_currentState;

    ret=applyAnimation();

    if(ret==EndAnimation)
    {
        //m_stepCurrentTime=0;
        if(step()==EnterAnimation)
        {
            setStep(DisplayAnimation);
            //m_timerAnimation.restart();
            m_stepCurrentTime=0;
            //qDebug() << "enter->display";
        }
        else
        {
            if(step()==DisplayAnimation)
            {
                setStep(ExitAnimation);
                //m_timerAnimation.restart();
                m_stepCurrentTime=0;
                //qDebug() << "display->exit";
                // if(m_showType==IN)
                // remove_old_items...

                if(m_currentSlideIndex+1<m_sequence->rowCount())
                {
                    index=m_sequence->index(m_currentSlideIndex+1);
                    if(index.isValid())
                    {
                        //if(m_showType==OUT)
                        val=index.data(Qt::UserRole);
                        itemNode=val.value<node>();

                        if(m_exportToMovie)
                        {
                            pix.load(itemNode.nodePath());
                        }
                        else
                        {
                            pix=itemNode.nodePixmap();
                        }

                        m_currentNode=itemNode;

                        if(pix.width()>m_size.width() || pix.height()>m_size.height())
                            pix=pix.scaled(m_size,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                        item = new Pixmap(pix);

                        if(m_exportToMovie)
                            item->setTransformationMode(Qt::SmoothTransformation);

                        m_PixmapList.append(item); // serve questa lista?
                        if(m_size.width()>pix.width())
                        {
                            x=(m_size.width()-pix.width())/2;
                        }
                        else
                        {
                            x=0;
                        }


                        if(m_size.height()>pix.height())
                        {
                            y=(m_size.height()-pix.height())/2;
                        }
                        else
                        {
                            y=0;
                        }

                        item->setPos(qreal(x), qreal(y));
                        item->setZValue(qreal(m_sequence->rowCount()-m_currentSlideIndex-1));
                        m_scene->addItem(item);
                        //applyAnimation();
                    }

                }
                else
                {
                    qDebug()<<"index out of range";
                }

            }
            else
            {
                if(step()==ExitAnimation)
                {
                    item=m_PixmapList[m_currentSlideIndex];
                    m_scene->removeItem(item);

                    m_currentSlideIndex++;
                    if(m_currentSlideIndex<m_sequence->rowCount())
                    {

                     /*   index=m_sequence->index(m_currentSlideIndex);
                        if(index.isValid())
                        {
                            //if(m_showType==OUT)
                            val=index.data(Qt::UserRole);
                            itemNode=val.value<node>();
                            pix=itemNode.nodePixmap();
                            item = new Pixmap(pix);
                            m_PixmapList.append(item); // serve questa lista?
                            item->setPos(0.0, 0.0);
                            //item->setZValue(qreal(m_sequence->rowCount()-m_currentSlideIndex));
                            m_scene->addItem(item);
                            applyAnimation();
                        }*/

                        setStep(EnterAnimation);
                        //m_timerAnimation.restart();
                        m_stepCurrentTime=0;
                    }
                    else
                    {
                        // end
                        //endOfSlideShow();
                        return Finished;
                    }


                } // if(step()==ExitAnimation)
                else
                {



                } // else if(step()==ExitAnimation)



            } // else if(step()==DisplayAnimation)



        } // else if(step()==EnterAnimation)



    } // if(ret==EndAnimation)
    //m_stepCurrentTime++;
    //m_totalCurrentTime++;


    if(m_exportToMovie)
    {        
        QImage frame(m_size,QImage::Format_RGB32);
        QPainter p(&frame);
        m_scene->render(&p);
        p.end();

        //QString frameName=QString("./tmp/f%1").arg(m_frame_number++);
        //frameName.append(".jpg");
        //frame.save(frameName);
        //encoder.encodeImage(frame);

        QByteArray dati;
        QBuffer buffer(&dati);
        buffer.open(QIODevice::WriteOnly);        
        frame.save(&buffer, "JPG");
        m_ffmpegProcess.write(buffer.buffer());
        m_ffmpegProcess.waitForBytesWritten();

        //QString command;
        ////m_ffmpegProcess.start("/usr/bin/ffmpeg", QStringList() << "-y -f image2pipe -i pipe:.jpg -target ntsc-dvd my.mpg");

        //command=QString("/usr/bin/ppmtoy4m -v 0 -n 1 -F 25:1 -S 420jpeg");


        //m_ffmpegProcess.write(EOF);
        //command.append(" -F 25:1 -S 420jpeg ");
        //command.append(buffer.buffer());


       //qDebug() << command;



        //dati=m_ffmpegProcess.readAllStandardOutput();


        //m_ffmpegProcess.write(buffer.buffer());
        //frame.save(m_ffmpegProcess);
        //m_ffmpegProcess << frameName;
        //ffmpeg -y -f image2pipe -i pipe:.jpg -target ntsc-dvd my.mpg



    }



    return Running;

}



void slideShowEngine::timerEvent(QTimerEvent *event)
{    
Q_UNUSED(event);

    if(m_currentState==Running)
    {
        int elapsed=m_timerAnimation.elapsed();

       //qDebug() << "ENTER TIMER EVENT" << elapsed;
        m_totalCurrentTime+=elapsed;
        m_stepCurrentTime+=elapsed;

        //m_totalCurrentTime+=25;
        //m_stepCurrentTime+=25;


        m_timerAnimation.start();


        m_currentState=runEngine();
        if(m_currentState==Running)
         emit refresh(m_totalCurrentTime);
        else
            if(m_currentState==Finished)
             endOfSlideShow();


        //elapsed=m_timerAnimation.elapsed();
        //qDebug() << "exit timer event"<<elapsed;


        //qDebug() << m_timerAnimation.elapsed();
        //qDebug() << m_totalCurrentTime;
    }



}

/*
QPixmap slideShowEngine::loadImage(int slideIndex)
{
 QPixmap pix;
 QModelIndex index;
 QVariant val;
 node itemNode;

    index=m_sequence->index(slideIndex);
    if(index.isValid())
    {
        val=index.data(Qt::UserRole);
        itemNode=val.value<node>();
        if(m_exportToMovie)
        {
            pix.load(itemNode.nodePath());
        }
        else
        {
            pix=itemNode.nodePixmap();
        }
    }
    return pix;
}*/


void slideShowEngine::start()
{
int x,y;

QPixmap pix;
QModelIndex index;
QVariant val;
node itemNode;
//QPropertyAnimation *enterAnimation,*displayAnimation,*exitAnimation;
Pixmap *item;
effect e;
//QParallelAnimationGroup *parallelAnim;
//QSequentialAnimationGroup *seqAnim;


    if(state()==Paused)
        resume();

    if(state()==Running)
        return;


    //QList <QGraphicsView *> views=m_scene->views();
    //m_size=views.at(0)->size();
    //int s=views.size();

    m_frame_number=0;
    m_scene->clear();    
    m_scene->setSceneRect(0.0,0.0,qreal(m_size.width()),qreal(m_size.height()));
    m_currentSlideIndex=0;
    index=m_sequence->index(m_currentSlideIndex);
    if(index.isValid())
    {
        m_currentState=Running;
        m_currentStep=EnterAnimation;
        //m_totalCurrentTime=0;
        //m_stepCurrentTime=0;

        val=index.data(Qt::UserRole);
        itemNode=val.value<node>();

        if(m_exportToMovie)
        {
            pix.load(itemNode.nodePath());
        }
        else
        {
            pix=itemNode.nodePixmap();
        }

        m_currentNode=itemNode;
        if(pix.width()>m_size.width() || pix.height()>m_size.height())
            pix=pix.scaled(m_size,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        item = new Pixmap(pix);
        if(m_exportToMovie)
            item->setTransformationMode(Qt::SmoothTransformation);
        m_PixmapList.append(item); // serve questa lista?
        if(m_size.width()>pix.width())
        {
            x=(m_size.width()-pix.width())/2;
        }
        else
        {
            x=0;
        }


        if(m_size.height()>pix.height())
        {
            y=(m_size.height()-pix.height())/2;
        }
        else
        {
            y=0;
        }

        item->setPos(qreal(x), qreal(y));
        item->setZValue(qreal(m_sequence->rowCount()-m_currentSlideIndex));
        m_scene->addItem(item);
        applyAnimation();
        //m_timerId=startTimer(TIMER_ANIMATION);
    }



    m_totalCurrentTime=0;
    m_stepCurrentTime=0;

    /*int width=m_sequence->movieResolution().width();
    int height=m_sequence->movieResolution().height();
    int bitrate=m_sequence->movieBitRate();*/
    int frameRate=m_sequence->movieFrameRate();
    //int gop = 20;

    if(m_exportToMovie)
    {
        //encoder.createFile(m_movieName,width,height,bitrate,gop,frameRate);
        QEventLoop evt;
        int frames=0;

        while(m_currentState!=Finished && m_currentState!=Stopped)
        {
           m_currentState=runEngine();
           if(m_currentState==Running)
            emit refresh(m_totalCurrentTime);
           evt.processEvents();


           if(m_currentState==Running)
           {
               //int elapsed=m_timerAnimation.elapsed();
               //qDebug() << elapsed;
               int period=1000/frameRate;
               m_totalCurrentTime+=period;
               m_stepCurrentTime+=period;
               m_timerAnimation.start();
           }
           frames++;

        }
        qDebug() << "frames:" << frames;
        endOfSlideShow();

     }
    else
    {
        startSound();
        m_timerId=startTimer(25); // TIMER_ANIMATION
        m_timerAnimation.start();        
    }

    //State state=Running;
    //m_timerAnimation.start();
    //m_totalTime.start();       
    //qDebug("Time elapsed: %d ms", t.elapsed());
}



void slideShowEngine::endOfSlideShow()
{
    m_scene->clear();    
    m_PixmapList.clear();

    killTimer(m_timerId);



    if(m_exportToMovie)
    {
        m_ffmpegProcess.write("\n");
        m_ffmpegProcess.waitForBytesWritten();

        ///////////////////////////////////////////////
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        int terminated=false;
        QByteArray data;
        while(!terminated)
        {
            m_ffmpegProcess.waitForReadyRead(2000);
            data=m_ffmpegProcess.readAll();
            if(data.isEmpty())
                terminated=true;
            //qDebug() << data;
        }
        QApplication::restoreOverrideCursor();
        /////// sporco modo x capire che ha finito! ///


        m_ffmpegProcess.terminate();
        m_ffmpegProcess.waitForFinished();

        // add audio
        /*QString commandString;
        commandString.append("/usr/bin/ffmpeg -y -i tmp.mpg -i ");

        for(int i=0; i<m_sequence->soundtracks().count();i++)
        {
            commandString.append(m_sequence->soundtracks().at(i));
            commandString.append(" ");

        }

        commandString.append(m_movieName);
        m_ffmpegProcess.start(commandString);
        m_ffmpegProcess.waitForFinished();*/

        QString commandString;
        commandString="rm __track__.wav";
        QProcess clearCommand;
        clearCommand.setProcessChannelMode(QProcess::ForwardedChannels);
        clearCommand.start(commandString);
        clearCommand.waitForFinished();


        //qDebug() << "add audio finished";
    }
    else
    {
        m_mplayerProcess.terminate();
        m_mplayerProcess.waitForFinished();
    }

    emit finished();
}



void slideShowEngine::pause()
{
    m_currentState=Paused;
    pauseSound();
    //storeTimerAnimation=m_timerAnimation.elapsed();
    //storeTotalTime=m_totalTime.elapsed();
    //m_groupAnimation->pause();
}

void slideShowEngine::resume()
{            
    //m_groupAnimation->resume();
    if(m_currentState==Paused)
    {
        //storeTimerAnimation=m_timerAnimation.elapsed();
        //m_timerAnimation.start();
        //m_timerAnimation=m_timerAnimation.addMSecs(-storeTimerAnimation);
        //m_totalTime.restart();
        //m_totalTime=m_totalTime.addMSecs(storeTotalTime);
        m_currentState=Running;
        m_timerAnimation.start();
        resumeSound();
    }

}
void slideShowEngine::stop()
{
    m_currentState=Stopped;
    endOfSlideShow();
}



slideShowEngine::AnimationState slideShowEngine::applyAnimation()
{
effect e;
QEasingCurve curve;
qreal currentValue;
Pixmap *item;

    if(m_currentStep==EnterAnimation)
        e=m_currentNode.enterEffect();
    else
        if(m_currentStep==DisplayAnimation)
            e=m_currentNode.displayEffect();
        else
            if(m_currentStep==ExitAnimation)
                e=m_currentNode.exitEffect();

    int duration=e.duration();
    //int elapsed=m_stepCurrentTime;
    curve.setPeriod(duration);
    qreal startVal=qreal(e.startValue());
    qreal endVal=qreal(e.endValue());

    curve.setType(e.easingCurve());
    //qreal valore=qreal(m_stepCurrentTime*TIMER_ANIMATION);
    qreal valore=qreal(m_stepCurrentTime);
    //qreal valore=qreal(m_stepCurrentTime*10);
    valore=valore/(qreal(duration));
    //valore=valore/10;
    //currentValue=curve.valueForProgress(valore);
    currentValue=endVal+(1.0-curve.valueForProgress(valore))*(startVal-endVal);    


    item=m_PixmapList[m_currentSlideIndex];

    if(e.effectType()=="pos")
        item->setProperty(e.effectType().toLatin1(),QVariant(QPointF(currentValue,0)));
    else
        item->setProperty(e.effectType().toLatin1(),QVariant(currentValue));


    //if(m_stepCurrentTime*TIMER_ANIMATION < e.duration()/**10*/)
    if(m_stepCurrentTime < duration)
    //if(m_stepCurrentTime*10 < e.duration()/**10*/)
        return RunningAnimation;
    else
        return EndAnimation;

}


/*
int slideShowEngine::totalTimeDuration()
{
    QModelIndex index;
    QVariant val;
    node itemNode;
    int totalTime=0;

    for(int i=0; i<m_sequence->rowCount();i++)
    {
        index=m_sequence->index(i);
        if(index.isValid())
        {

            val=index.data(Qt::UserRole);
            itemNode=val.value<node>();

            totalTime+=itemNode.enterEffect().duration();
            totalTime+=itemNode.displayEffect().duration();
            totalTime+=itemNode.exitEffect().duration();
        }
    }
    return totalTime;
}
*/




void slideShowEngine::setExportMovie(QString movieName)
{
    m_exportToMovie=true;
    m_movieName=movieName;

    // prepare audio track
    QProcess soxCommand;
    QString commandString=QString("/usr/bin/sox ");

    for(int i=0; i<m_sequence->soundtracks().count();i++)
    {
        commandString.append(m_sequence->soundtracks().at(i));
        commandString.append(" ");

    }
    commandString.append(" __track__.wav");
    //soxCommand.setProcessChannelMode(QProcess::ForwardedChannels);
    m_ffmpegProcess.setProcessChannelMode(QProcess::MergedChannels);
    soxCommand.start(commandString);
    soxCommand.waitForFinished();


    commandString=QString("/usr/bin/ffmpeg -r ");   // frame rate
    commandString.append(QString("%1").arg(m_sequence->movieFrameRate()));

    commandString.append(" -b ");   // bit rate
    commandString.append(QString("%1").arg(m_sequence->movieBitRate()));

    commandString.append(" -s ");  // video size
    QString videoSize=QString("%1x%2").arg(m_sequence->movieResolution().width()).arg(m_sequence->movieResolution().height());
    commandString.append(videoSize);
    commandString.append(" -y -f image2pipe -i pipe:.jpg ");
    commandString.append(" -i __track__.wav ");


    //commandString.append("-target ntsc-dvd ");
    commandString.append(m_movieName);

    qDebug() << commandString;
    //m_ffmpegProcess.setProcessChannelMode(QProcess::ForwardedChannels);
    m_ffmpegProcess.setProcessChannelMode(QProcess::MergedChannels);
    m_ffmpegProcess.start(commandString);


}


void slideShowEngine::resetExportMovie()
{
    m_exportToMovie=false;
}

