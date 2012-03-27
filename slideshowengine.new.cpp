#include "mainwindow.h"
#include "slideshowengine.h"

slideShowEngine::slideShowEngine(QWidget *parent) :
    QWidget(parent)
{
    m_currentSlideIndex=0;
    m_groupAnimation = new QSequentialAnimationGroup;
}

slideShowEngine::~slideShowEngine()
{

    m_groupAnimation->clear(); // basta anche per le animazioni parallele?
    // scan m_groupAnimation and delete all the animations
    /*for(int i=0; i<m_PixmapList.size()-1;i++)
    {
       Pixmap *item = m_PixmapList[i];
       delete item;
    }*/

    m_PixmapList.clear();
    delete m_groupAnimation;

}

void slideShowEngine::setCurrentTime(int time)
{
    //if(time>m_groupAnimation->currentTime()) // no backward direction
        //m_groupAnimation->setCurrentTime(time);
   // qDebug() << "not yet implemented: some problem to fix...";
}

void slideShowEngine::timerEvent(QTimerEvent *event)
{
    //int elapsedTime=m_slideShowClock.elapsed();
    //qDebug() << elapsedTime;

    //qDebug()<< "render";

    killTimer(m_timerId);
    m_groupAnimation->pause();

    QImage frame(640,480,QImage::Format_RGB32);

    //QImage img(640,480,QImage::Format_ARGB32_Premultiplied);
    QPainter p(&frame);
    m_scene->render(&p);
    p.end();
    //encoder.encodeImage(frame);
    m_groupAnimation->resume();
    m_timerId=startTimer(2);
    //img.save("scene.png");





}

void slideShowEngine::start()
{
int x,y;
QPixmap pix;
QModelIndex index;
QVariant val;
node itemNode;
QPropertyAnimation *enterAnimation,*displayAnimation,*exitAnimation;
Pixmap *item;
effect e;
QParallelAnimationGroup *parallelAnim;
QSequentialAnimationGroup *seqAnim;



    if(m_groupAnimation->state()==QAbstractAnimation::Paused)
        resume();

    if(m_groupAnimation->state()==QAbstractAnimation::Running)
        return;

    QList <QGraphicsView *> views=m_scene->views();
    m_size=views.at(0)->size();

    m_scene->clear();
    for(int i=0;i<m_sequence->rowCount();i++)
    {

        index=m_sequence->index(i);
        if(index.isValid())
        {
            m_scene->setSceneRect(0.0,0.0,qreal(m_size.width()),qreal(m_size.height())); // come fare per full screen size?
            qDebug() << "index valid";
            val=index.data(Qt::UserRole);
            itemNode=val.value<node>();
            qDebug() << "pix:" << itemNode.nodeName();
            pix=itemNode.nodePixmap();

            if(pix.width()>m_size.width() || pix.height()>m_size.height())
                pix=pix.scaled(m_size,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            item = new Pixmap(pix);
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


            qDebug() <<qreal(m_sequence->rowCount()-i);
            item->setZValue(qreal(m_sequence->rowCount()-i));
            //m_scene->addItem(item);

            e=itemNode.enterEffect();
            enterAnimation = new QPropertyAnimation(item, e.effectType().toAscii());
            itemNode.setEnterAnimation(enterAnimation,item);
            connect(enterAnimation,SIGNAL(finished()),this,SLOT(animEnterFinished()));

            e=itemNode.displayEffect();
            displayAnimation = new QPropertyAnimation(item, e.effectType().toAscii());
            itemNode.setDisplayAnimation(displayAnimation,item);
            connect(displayAnimation,SIGNAL(finished()),this,SLOT(animDisplayFinished()));

            e=itemNode.exitEffect();
            exitAnimation = new QPropertyAnimation(item, e.effectType().toAscii());
            itemNode.setExitAnimation(exitAnimation,item);
            connect(exitAnimation,SIGNAL(finished()),this,SLOT(animExitFinished()));


            //parallelAnim= new QParallelAnimationGroup;

            //parallelAnim->addAnimation(exitAnimation);

            seqAnim = new QSequentialAnimationGroup;

            seqAnim->addAnimation(enterAnimation);
            seqAnim->addAnimation(displayAnimation);
            seqAnim->addAnimation(exitAnimation);


            qDebug() << "add all animation";

            m_groupAnimation->addAnimation(seqAnim);
            connect(m_groupAnimation,SIGNAL(finished()),this,SLOT(endOfSlideShow()));

            //group->addAnimation(animation4);

        } // end index is valid

    } // end for

    qDebug() << "start group";
    m_currentSlideIndex=0;
    m_scene->addItem(m_PixmapList.at(m_currentSlideIndex));
    m_groupAnimation->start();           
    //m_timerId=startTimer(2);
    //m_slideShowClock.restart();



    int width=640;
    int height=480;
    int bitrate=1000000;
    int gop = 20;


    // Create the encoder
    //QVideoEncoder encoder;
    //encoder.createFile("test.avi",width,height,bitrate,gop);




}



void slideShowEngine::animEnterFinished()
{


}

void slideShowEngine::animDisplayFinished()
{
   // qDebug()<<"display finished";
    if(m_currentSlideIndex<m_PixmapList.size()-1)
    {
         m_scene->addItem(m_PixmapList.at(m_currentSlideIndex+1));
    }
}


void slideShowEngine::animExitFinished()
{

    if(m_currentSlideIndex<m_PixmapList.size())
    {
        m_scene->removeItem(m_PixmapList[m_currentSlideIndex]);
        m_currentSlideIndex++;

    }



}


void slideShowEngine::endOfSlideShow()
{
    m_scene->clear();
    m_groupAnimation->clear(); // basta anche per le animazioni parallele?
    m_PixmapList.clear();
    emit finished();
    //encoder.close();
    killTimer(m_timerId);
}



void slideShowEngine::pause()
{
    m_groupAnimation->pause();
}

void slideShowEngine::resume()
{
    m_groupAnimation->resume();
}
void slideShowEngine::stop()
{
    m_groupAnimation->stop();
    m_groupAnimation->setCurrentTime(0);
    endOfSlideShow();   
}


void slideShowEngine::setExportMovie(QString movieName)
{
    m_exportToMovie=true;
    m_movieName=movieName;
}


void slideShowEngine::resetExportMovie()
{
    m_exportToMovie=false;
}
