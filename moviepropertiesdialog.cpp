#include "moviepropertiesdialog.h"
#include "ui_moviepropertiesdialog.h"

moviePropertiesDialog::moviePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::moviePropertiesDialog)
{
    ui->setupUi(this);
    connect(ui->applyButton,SIGNAL(released()),this,SLOT(applySlot()));

}

moviePropertiesDialog::~moviePropertiesDialog()
{
    delete ui;
}



void moviePropertiesDialog::setModelData(sequenceModel *model)
{
    m_model=model;

    ui->resolutionCombo->setCurrentIndex(indexFromResolution(m_model->movieResolution()));
    QString str=QString("%1").arg(m_model->movieBitRate());
    ui->bitRate->setText(str);
    str=QString("%1").arg(m_model->movieFrameRate());
    ui->frameRate->setText(str);

}


void moviePropertiesDialog::applySlot()
{

    int resolutionIndex=ui->resolutionCombo->currentIndex();
    m_model->setMovieResolution(resolutionFromIndex(resolutionIndex));

    QString str=ui->bitRate->text();
    int bitRate=str.toInt();
    m_model->setMovieBitRate(bitRate);
    str=ui->frameRate->text();
    int frameRate=str.toInt();
    m_model->setMovieFrameRate(frameRate);

}



QSize moviePropertiesDialog::resolutionFromIndex(int index)
{

    switch(index)
    {
    case 0: return QSize(320,240);break;
    case 1: return QSize(640,480);break;
    case 2: return QSize(800,600);break;
    case 3: return QSize(1024,768);break;
    case 4: return QSize(1280,1024);break;
    case 5: return QSize(1600,1200);break;
    default: return QSize(640,480);break;
    }
}


int moviePropertiesDialog::indexFromResolution(QSize size)
{

    if(size.width()==320)
        return 0;
    else
        if(size.width()==640)
            return 1;
        else
            if(size.width()==800)
                return 2;
            else
                if(size.width()==1024)
                    return 3;
                else
                    if(size.width()==1280)
                        return 4;
                    else
                        if(size.width()==1600)
                          return 5;
                        else
                          return 1;
}



