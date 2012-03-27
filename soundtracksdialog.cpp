#include "soundtracksdialog.h"
#include "ui_soundtracksdialog.h"

soundtracksDialog::soundtracksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::soundtracksDialog)
{
    ui->setupUi(this);
    mSTotalDuration=0;
    ui->tracksView->setCornerButtonEnabled(false);
    ui->tracksView->setAlternatingRowColors(true);
    connect(ui->upButton,SIGNAL(released()),this,SLOT(goUpSlot()));
    connect(ui->downButton,SIGNAL(released()),this,SLOT(goDownSlot()));
    connect(ui->plusButton,SIGNAL(released()),this,SLOT(addSlot()));
    connect(ui->minusButton,SIGNAL(released()),this,SLOT(removeSlot()));
    connect(ui->arrangeTimeButton,SIGNAL(released()),this,SLOT(arrangeTimeSlot()));


    ui->tracksView->horizontalHeader()->setStretchLastSection(true);

    //ui->tracksView->verticalHeader()->hide();
}

soundtracksDialog::~soundtracksDialog()
{
    delete ui;
}

void soundtracksDialog::setModelData(sequenceModel *model)
{
    m_model=model;
    /*QStringList list=model->soundtracks();

    for(int i=0; i<list.count();i++)
    {
        QFileInfo file(list[i]);
        QTableWidgetItem *item = new QTableWidgetItem(file.fileName());
        ui->tracksView->insertRow(i);
        ui->tracksView->setItem (i, 0,item);
        ui->tracksView->resizeColumnsToContents();
    }*/

    trackStats();

}


void soundtracksDialog::trackStats()
{
QProcess ffmpeg;
QString command;
QByteArray result;
QString duration;

QRegExp rx("Duration: ([0-9]+):([0-9]+):([0-9]+)\\.([0-9]+)");

/*mplayer o ffplay
QRegExp rx_clip_name("^ (name|title): (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_artist("artist: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_author("^ author: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_album("^ album: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_genre("^ genre: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_date("^ (creation date|year): (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_track("^ track: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_copyright("^ copyright: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_comment("^ comment: (.*)", Qt::CaseInsensitive);
QRegExp rx_clip_software("^ software: (.*)", Qt::CaseInsensitive);*/


        ffmpeg.setProcessChannelMode(QProcess::MergedChannels);
        //ffmpeg.setProcessChannelMode(QProcess::ForwardedChannels);

        int rows=ui->tracksView->rowCount();
        for(int i=0;i<rows;i++)
            ui->tracksView->removeRow(0);

        QStringList list=m_model->soundtracks();
        mSTotalDuration=0;
        for(int i=0; i<list.count();i++)
        {
            command="/usr/bin/ffmpeg -i ";
            command.append(list[i]);
            //qDebug() << command;
            ffmpeg.start(command);
            ffmpeg.waitForFinished();
            result = ffmpeg.readAll();

            QString str(result);

            QFileInfo file(list[i]);
            QTableWidgetItem *item = new QTableWidgetItem(file.fileName());
            item->setFlags(item->flags()&~Qt::ItemIsEditable);
            ui->tracksView->insertRow(i);
            ui->tracksView->setItem (i, 0,item);

            if (rx.indexIn(str) > -1)
            {
                duration=rx.cap(1);
                duration.append(":");
                duration.append(rx.cap(2));
                duration.append(":");
                duration.append(rx.cap(3));
                duration.append(".");
                duration.append(rx.cap(4));

                mSTotalDuration+=rx.cap(4).toInt()*10;
                mSTotalDuration+=rx.cap(3).toInt()*1000;
                mSTotalDuration+=rx.cap(2).toInt()*60000;

                QTableWidgetItem *item2 = new QTableWidgetItem(duration);
                item2->setFlags(item->flags()&~Qt::ItemIsEditable);
                ui->tracksView->setItem (i, 1,item2);


            }
            else
                qDebug() << "soundtrack info not found";

        }

        ui->tracksView->resizeColumnsToContents();
        ui->tracksView->horizontalHeader()->setStretchLastSection(true);

        //int slideShowDuration=m_model->slideShowDuration();
        int slideShowDuration=m_model->duration();
        ui->slideShowTimeLabel->setText(QString("%1").arg(slideShowDuration));
        ui->soundTrackTimeLabel->setText(QString("%1").arg(mSTotalDuration));
        int maximum=qMax(slideShowDuration,mSTotalDuration);

        ui->soudtrackTime->setMaximum(maximum);
        ui->slideShowTime->setMaximum(maximum);

        ui->soudtrackTime->setValue(mSTotalDuration);
        ui->slideShowTime->setValue(slideShowDuration);

        rows=ui->tracksView->rowCount();
        ui->nTracksLabel->setText(QString("%1").arg(rows));
        ui->nSlidesLabel->setText(QString("%1").arg(m_model->rowCount()));


}




void soundtracksDialog::goUpSlot()
{
    int currentTrack=ui->tracksView->currentRow();
    if(currentTrack>0)
    {
        m_model->swapSoundtrack(currentTrack,currentTrack-1);
        trackStats();
    }

}

void soundtracksDialog::goDownSlot()
{
    int currentTrack=ui->tracksView->currentRow();
    if(currentTrack<ui->tracksView->rowCount()-1 && currentTrack!=-1)
    {
        m_model->swapSoundtrack(currentTrack,currentTrack+1);
        trackStats();
    }

}

void soundtracksDialog::removeSlot()
{

    if(m_model->soundtracks().count()<1)
        return;
    QMessageBox msgBox;
    msgBox.setText(tr("Sondtrack"));
    msgBox.setInformativeText(tr("Do you want to remove the current Track?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Cancel)
        return;

    int currentTrack=ui->tracksView->currentRow();
    m_model->removeSoundtrack(currentTrack);
    //ui->tracksView->removeRow(currentTrack);
    trackStats();
}

void soundtracksDialog::addSlot()
{

    QString fileName;
    static QString currentPath(".");

    //qDebug() << "add soundtrack";

    fileName=QFileDialog::getOpenFileName(this,tr("Open"),currentPath, "Audio (*.mp2 *.ogg *.mp3 *.wav)");

    if (!fileName.isEmpty())  // if fileName is not empty
    {
        m_model->addSoundtrack(fileName);
    }
    trackStats();

}



void soundtracksDialog::arrangeTimeSlot()
{
    node item;
    effect e;
    QModelIndex index;    
    int slides=m_model->rowCount();
    int slideShowDurationTime=m_model->duration();


    int increment=(mSTotalDuration-slideShowDurationTime)/slides;


    for(int i=0; i<slides; i++)
    {
        index=m_model->index(i);
        QVariant val=index.data(Qt::UserRole);
        item=val.value<node>();

        e=item.displayEffect();
        e.setDuration(e.duration()+increment);
        item.setDisplayEffect(e);

        val.setValue(item);
        m_model->setData(index,val,Qt::EditRole);


    }









    trackStats();
}


