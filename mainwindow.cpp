#include <QtGui>
#include "const.h"
#include "effect.h"
#include "node.h"
#include "pixmap.h"
#include "delegate.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nodepropertiesdialog.h"
#include "slideshowengine.h"
#include "moviepropertiesdialog.h"
#include "soundtracksdialog.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_item1=0;
    ui->setupUi(this);

    readSettings();

    QString title=QString(APP_NAME);

    setWindowTitle(title);

    // The engine
    m_engine= new slideShowEngine;
    if(m_engine==0)
    {
        qDebug() << "error while creating the engine";
        return;
    }

    // The Model
    m_sequence = new sequenceModel;
    if(m_sequence==0)
    {
        qDebug() << "error while creating the Model";
        return;
    }
    connect(m_sequence,SIGNAL(dataChanged (QModelIndex,QModelIndex)),this,SLOT(modelChanged(QModelIndex,QModelIndex)));

    ui->listView->setModel(m_sequence);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(listClicked(QModelIndex)));
    connect(ui->listView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(listDoubleClicked(QModelIndex)));

    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(fileNewSlot()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(fileOpenSlot()));
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(fileCloseSlot()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(fileSaveSlot()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(fileSaveAsSlot()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exitSlot()));
    connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(exportToMovie()));
    connect(ui->actionOptions,SIGNAL(triggered()),this,SLOT(movieOptionsSlot()));

    connect(ui->actionManage_Soundtrack,SIGNAL(triggered()),this,SLOT(manageSoundtracks()));

    createListContextMenu();
    connect(ui->listView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(listContextMenuRequested(QPoint)));

    connect(ui->actionPreview,SIGNAL(triggered()),this,SLOT(startSlideShowEngine()));
    connect(ui->startButton,SIGNAL(released()),this,SLOT(startSlideShowEngine()));

    // The Delegate
    m_delegate = new delegate;
    ui->listView->setItemDelegate(m_delegate);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
      //                             | QAbstractItemView::SelectedClicked);
    ui->listView->setSelectionBehavior(QAbstractItemView::SelectItems);

    // The View
    m_scene=new QGraphicsScene;
    ui->graphicsView->setScene(m_scene);    

    // set filters = all supported file formats. New plugins will automatically add new image formats
    QList <QByteArray> supportedFilters;
    QStringList filters;
    QString extensionFilter;
    QImageReader reader;

    supportedFilters = reader.supportedImageFormats();

    for (int i = 0; i < supportedFilters.size(); ++i)  // fill supported file extensions
    {
        extensionFilter.append("*.");
        extensionFilter.append(supportedFilters[i]);
        filters.append(extensionFilter);
        extensionFilter.clear();

    }

    m_FileSystemModel.setRootPath("");
    m_FileSystemModel.setNameFilters(QStringList(filters));
    ui->dirView->setModel(&m_FileSystemModel);

    connect(ui->dirView,SIGNAL(clicked(QModelIndex)),this,SLOT(dirViewClickSlot(QModelIndex)));
    connect(ui->dirView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(dirViewDoubleClickSlot(QModelIndex)));

    ui->dirView->setColumnHidden(1,true);
    ui->dirView->setColumnHidden(2,true);
    ui->dirView->setColumnHidden(3,true);
    ui->dirView->setHeaderHidden(true);

    ui->dirView->setAnimated(false);
    ui->dirView->setIndentation(20);
    ui->dirView->setSortingEnabled(true);
    ui->dirView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_sequence;
    delete m_delegate;
    delete m_engine;
    m_scene->clear();
}



void MainWindow::listClicked(const QModelIndex & index)
{
int x,y;

    if((m_engine->state()==slideShowEngine::Paused) || (m_engine->state()==slideShowEngine::Running))
    {
        statusBar()->showMessage(tr("Slide Show Running"), 2000);
        return;
    }

    QList <QGraphicsView *> views=m_scene->views();
    QSize m_size=views.at(0)->size();

    QVariant val=index.data(Qt::UserRole);
    node itemNode=val.value<node>();
    m_scene->clear();   
    QPixmap pix=itemNode.nodePixmap();

    if(pix.width()>m_size.width() || pix.height()>m_size.height())
        pix=pix.scaled(m_size,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    m_item1 = new Pixmap(pix);

    if(m_size.width()>pix.width())    
        x=(m_size.width()-pix.width())/2;   
    else   
        x=0;    

    if(m_size.height()>pix.height())    
        y=(m_size.height()-pix.height())/2;
    else
        y=0;

    m_item1->setPos(qreal(x), qreal(y));
    m_scene->addItem(m_item1);
}


void MainWindow::listDoubleClicked(const QModelIndex & index)
{
    Q_UNUSED(index);
    createEditor();
}

void MainWindow::dirViewClickSlot(QModelIndex index)
{
    int x,y;

    QString filePath = m_FileSystemModel.filePath(index);
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QPixmap pix(filePath);
    if(pix.isNull())
    {
        QApplication::restoreOverrideCursor();
        return;
    }




    if(pix.width()>PREVIEW_WIDTH || pix.height()>PREVIEW_HEIGHT)
        pix=pix.scaled(QSize(PREVIEW_WIDTH,PREVIEW_HEIGHT),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    m_item1 = new Pixmap(pix);

    if(PREVIEW_WIDTH > pix.width())
        x=(PREVIEW_WIDTH-pix.width())/2;
    else
        x=0;

    if(PREVIEW_HEIGHT>pix.height())
        y=(PREVIEW_HEIGHT-pix.height())/2;
    else
        y=0;

    m_item1->setPos(qreal(x), qreal(y));
    m_scene->clear();
    m_scene->addItem(m_item1);






    // manca il preview dell'immagine selezionata sulla treeview!!!!!!!!!!!!!!!!!!!!!!
    /*if(pix.width()> ui->label->width() || pix.height() > ui->label->height())
        pix=pix.scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setPixmap(pix);*/
    /////////////////////////////////////////////////////////////////////////////////


    QApplication::restoreOverrideCursor();
}



void MainWindow::dirViewDoubleClickSlot(QModelIndex index)
{
    QString filePath = m_FileSystemModel.filePath(index);
    if(filePath.isNull() || filePath.isEmpty())
        return;

    QPixmap pix(filePath);
    if(pix.isNull())
    {
        return;
    }

    // questo va fatto meglio... non può stare così! O richiami propertyDialog
    // o imposti meglio il nodo da inserire!!!!!
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    node item;
    item.setNodePixmap(pix);
    item.setNodePath(filePath);
    item.setNodeName(QFileInfo(filePath).baseName());
    effect e;
    e.setEffectType("pos");
    e.setStartPointF(QPointF(0.0,0.0));
    e.setEndPointF(QPointF(0.0,0.0));
    e.setDuration(2000);
    e.setEasingCurve(QEasingCurve::OutQuad);
    item.setDisplayEffect(e);
    e.setEndPointF(QPointF(640.0,0.0));
    e.setDuration(2000);
    item.setExitEffect(e);
    QVariant v;
    v.setValue(item);
    m_sequence->appendRow(v);
    ui->actionPreview->setEnabled(true);
    ui->startButton->setEnabled(true);

    QApplication::restoreOverrideCursor();
}


void MainWindow::createListContextMenu()
{
    m_listContextMenu = new QMenu;
    m_nodePropertyAct=m_listContextMenu->addAction(tr("Property"));
    m_removeNodeAct=m_listContextMenu->addAction(tr("Remove Slide"));
    //insertBeforeAct=m_listContextMenu->addAction(tr("InsertBefore"));
    //m_insertAfterAct=m_listContextMenu->addAction(tr("InsertAfter"));

    connect(m_nodePropertyAct,SIGNAL(triggered()),this,SLOT(createEditor()));
    connect(m_removeNodeAct,SIGNAL(triggered()),this,SLOT(removeItemInList()));

    //connect(insertBeforeAct,SIGNAL(triggered()),this,SLOT(insertBefore()));
    //connect(m_insertAfterAct,SIGNAL(triggered()),this,SLOT(insertAfter()));
}


void MainWindow::listContextMenuRequested(QPoint pos)
{
    QModelIndex index=ui->listView->currentIndex();

    if(index.isValid())
    {
        m_listContextMenu->popup(ui->listView->mapToGlobal(pos));
    }
}


void MainWindow::removeItemInList()
{

    if((m_engine->state()==slideShowEngine::Paused) || (m_engine->state()==slideShowEngine::Running))
    {
        statusBar()->showMessage(tr("Slide Show Running"), 2000);
        return;
    }


    QMessageBox msgBox;
    msgBox.setText(tr("Slide Show Sequence"));
    msgBox.setInformativeText(tr("Do you want to remove the Slide?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret==QMessageBox::Cancel)
        return;

    QModelIndex index=ui->listView->currentIndex();
    if(index.isValid())
    {
        m_sequence->removeRow(index.row());
    }
}


void MainWindow::createEditor()
{

    if((m_engine->state()==slideShowEngine::Paused) || (m_engine->state()==slideShowEngine::Running))
    {
        statusBar()->showMessage(tr("Slide Show Running"), 2000);
        return;
    }

    QModelIndex index=ui->listView->currentIndex();
    nodePropertiesDialog editor;
    editor.setEditorData(index);
    editor.setModelData(m_sequence);
    editor.exec();
}



void MainWindow::startSlideShowEngine()
{
   if(m_engine->state()==slideShowEngine::Paused)
        pauseSlideShowEngine();

    if(m_engine->state()==slideShowEngine::Running)
    {
        statusBar()->showMessage(tr("Slide Show Already Running"), 2000);
        return;
    }



    m_engine->setViewerSize(QSize(PREVIEW_WIDTH,PREVIEW_HEIGHT)); // this must be a parameter...

    ui->pauseButton->setText("Pause");
    m_scene->clear();
    m_engine->setViewer(m_scene);
    m_engine->setSequence(m_sequence);
    connect(ui->pauseButton,SIGNAL(released()),this,SLOT(pauseSlideShowEngine()));
    connect(ui->stopButton,SIGNAL(released()),this,SLOT(stopSlideShowEngine()));
    connect(ui->actionPause,SIGNAL(triggered()),this,SLOT(pauseSlideShowEngine()));
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(stopSlideShowEngine()));
    ui->pauseButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);
    //connect(m_engine,SIGNAL(finished()),this,SLOT(stopSlideShowEngine()));
    connect(m_engine,SIGNAL(finished()),this,SLOT(endSlideShow()));
    connect(m_engine,SIGNAL(refresh(int)),this,SLOT(slideShowProgress(int)));
    connect(m_engine,SIGNAL(refresh(int)),this,SLOT(slideShowProgress(int)));
    ui->timeBar->setMaximum(m_sequence->duration());

    //ui->totalDurationTime->display(m_engine->totalTimeDuration());

    ui->dirView->setEnabled(false);
    m_engine->start();
}


void MainWindow::slideShowProgress(int time)
{
    //connect(m_engine,SIGNAL(refresh(int)),ui->lcdNumber,SLOT(display(int)));
    //connect(m_engine,SIGNAL(refresh(int)),ui->timeBar,SLOT(setValue(int)));

    //ui->totalDurationTime->setText(QString("%1").arg(m_engine->totalTimeDuration()));
    //ui->currentTime->setText(QString("%1").arg(time));
    ui->timeBar->setValue(time);
    ui->lcdTime->display(time);
    //ui->totalDurationTime->display(0);


}

void MainWindow::endSlideShow()
{

    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);
    disconnect(ui->pauseButton,SIGNAL(released()),this,SLOT(pauseSlideShowEngine()));
    disconnect(ui->stopButton,SIGNAL(released()),this,SLOT(stopSlideShowEngine()));
    ui->dirView->setEnabled(true);
}



void MainWindow::stopSlideShowEngine()
{

    //questo slot gestisce anche il segnale di fine dell'engine e quindi il timer va fermato
    //anche se lo stato non è più running. Sarebbe meglio avere uno slot dedicato ai segnali dell'engine

    if(m_engine->state()!=slideShowEngine::Running && m_engine->state()!=slideShowEngine::Paused)
    {
        statusBar()->showMessage(tr("Slide Show Not Running"), 2000);
        return;
    }

    if(m_engine->exportToMovie())
        statusBar()->showMessage(tr("Writing to disk..."), 2000);

    m_engine->stop();
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);
    disconnect(ui->pauseButton,SIGNAL(released()),this,SLOT(pauseSlideShowEngine()));
    disconnect(ui->stopButton,SIGNAL(released()),this,SLOT(stopSlideShowEngine()));
}


void MainWindow::pauseSlideShowEngine()
{

    if(m_engine->state()!=slideShowEngine::Running && m_engine->state()!=slideShowEngine::Paused)
    {
        statusBar()->showMessage(tr("Slide Show Not Running"), 2000);
        return;
    }

    if(ui->pauseButton->text()=="Pause")
    {
        ui->pauseButton->setText("Resume");
        m_engine->pause();
    }
    else
    {
        ui->pauseButton->setText("Pause");
        m_engine->resume();
    }

}


/*void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    ui->timeBar->setMaximum(m_engine->totalTimeDuration());
    ui->totalDurationTime->display(m_engine->totalTimeDuration());
    ui->lcdNumber->display(m_engine->elapsedTime());
    ui->timeBar->setValue(m_engine->elapsedTime());
}*/



void MainWindow::fileNewSlot()
{

    if(m_sequence->rowCount()>0)
    {
        stopSlideShowEngine();
        fileCloseSlot();
        //free (m_engine);   // ????
    }

    QString title=QString(APP_NAME);
    //title.append(APP_VERSION);
    title.append(tr("-Untitled"));

    ui->actionSave->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
    ui->actionClose->setEnabled(true);
    ui->actionManage_Soundtrack->setEnabled(true);
    ui->actionExport->setEnabled(true);

    setWindowTitle(title);
}

void MainWindow::fileOpenSlot()
{
QString fileName;
static QString currentPath(".");

    if(m_sequence->rowCount()>0)
    {
        stopSlideShowEngine();
        fileCloseSlot();
    }



fileName=QFileDialog::getOpenFileName(this,tr("Open"),currentPath, "PhotoShow (*.phs)"); // show dialog


if (!fileName.isEmpty())  // if fileName is not empty
{

    m_slideShowFilePath=fileName;
    QString title=QString(APP_NAME);
    title.append(APP_VERSION);
    title.append("-");
    title.append(QFileInfo(fileName).baseName());
    setWindowTitle(title);

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    m_sequence->load(fileName);
    QApplication::restoreOverrideCursor();

    ui->startButton->setEnabled(true);
    ui->actionPreview->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
    ui->actionClose->setEnabled(true);
    ui->actionPreview->setEnabled(true);

    ui->startButton->setEnabled(true);
    ui->actionManage_Soundtrack->setEnabled(true);
    ui->actionExport->setEnabled(true);
}

}

void MainWindow::fileCloseSlot()
{
    QString title;

    if(m_sequence->rowCount()==0)

    {
        qDebug() << tr("no project existing");
        return;
    }

    ui->startButton->setEnabled(false);
    ui->actionPreview->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_As->setEnabled(false);
    ui->actionClose->setEnabled(false);

    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    ui->actionManage_Soundtrack->setEnabled(false);
    ui->actionExport->setEnabled(false);


    title=QString(APP_NAME);
    //title.append(APP_VERSION);
    title.append(tr("-Untitled"));
    setWindowTitle(title);

    stopSlideShowEngine();

    if(m_sequence->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("The project has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
           case QMessageBox::Save:
               // Save was clicked
                fileSaveSlot();
               break;
           default:
               // should never be reached
               break;
         }
    }

    // la close dovrebbe pulire tutte le view...    
    m_sequence->clear();
    m_scene->clear();

    slideShowProgress(0);
    ui->infoString->setText("");
    //ui->totalDurationTime->display(0);
    //ui->lcdNumber->display(0);
    //ui->timeBar->setValue(0);

}


void MainWindow::fileSaveSlot()
{
     if(m_sequence->rowCount()==0)

     {
         qDebug() << tr("no project existing");
         return;
     }

     if(m_slideShowFilePath.isEmpty() || m_slideShowFilePath.isNull())
       fileSaveAsSlot();
     else
     {
        m_sequence->save(m_slideShowFilePath);
     }

}

void MainWindow::fileSaveAsSlot()
{
QString filePath,selectedFilter;

    filePath=QFileDialog::getSaveFileName(this,
                                         tr("Save As..."),
                                         ".",
                                         "PhotoShow (*.phs)",
                                          &selectedFilter);


    if(!selectedFilter.isEmpty()) //check if selectedFilter is valid
    {
        if (!filePath.contains(".phs"))
            filePath.append(".phs");
    }


    if (!filePath.isEmpty() && !filePath.isNull()) // check if the name is valid
    {

        m_slideShowFilePath=filePath;
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        m_sequence->save(filePath);
        QApplication::restoreOverrideCursor();
        QString title=QString(APP_NAME);
        //title.append(APP_VERSION);
        title.append(tr("-Untitled"));

        title.append(QFileInfo(filePath).baseName());
        setWindowTitle(title);
    }

}

void MainWindow::exitSlot()
{
    fileCloseSlot();
    writeSettings();
    close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exitSlot();
}



/*!
  \brief readSettings: Reads registry settings
  \param void
  \return void
*/
void MainWindow::readSettings()
{
 QStringList sizeList;
 QList <int> sizes;


 QSettings settings(ORG_NAME, APP_NAME); // select which settings are you looking for
 QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint(); // get main window position
 QSize size = settings.value("size", QSize(400, 400)).toSize();  // get main window size
 move(pos);                                                      // move main window to this position
 resize(size);                                                   // resize main window


}


/*!
  \brief writeSettings: Writes registry settings
  \param void
  \return void
*/
void MainWindow::writeSettings()
{
  QStringList sizeList;
  QSettings settings(ORG_NAME, APP_NAME);  // save information about this application
  settings.setValue("pos", pos());         // save main window position
  settings.setValue("size", size());       // save main window size

}




void MainWindow::movieOptionsSlot()
{
   moviePropertiesDialog dialog;
   dialog.setModelData(m_sequence);
   dialog.exec();

}



void MainWindow::exportToMovie()
{
    QString fileName;
    static QString currentPath(".");

    fileName=QFileDialog::getSaveFileName(this,tr("Export Slide Show"),currentPath,
                                          "Movie (*.asf *. wmv *.avi *.flv *.gxf *.mks *.mpg *.mpeg *.mxf *.ogg)");

    if (!fileName.isEmpty())  // if fileName is not empty
    {

        movieOptionsSlot();

        m_engine->setViewerSize(m_sequence->movieResolution());
        QGraphicsScene m_renderScene;
        m_renderScene.clear();
        m_engine->setViewer(&m_renderScene);
        m_engine->setSequence(m_sequence);

        connect(ui->stopButton,SIGNAL(released()),this,SLOT(stopSlideShowEngine()));
        connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(stopSlideShowEngine()));
        ui->stopButton->setEnabled(true);
        ui->actionStop->setEnabled(true);       

        connect(m_engine,SIGNAL(refresh(int)),this,SLOT(slideShowProgress(int)));
        //connect(m_engine,SIGNAL(refresh(int)),ui->timeBar,SLOT(setValue(int)));


        ui->timeBar->setMaximum(m_sequence->duration());
        //ui->totalDurationTime->display(m_engine->totalTimeDuration());
        //ui->totalDurationTime->setText(QString("%1").arg(m_sequence->duration())); SERVE??????????

        m_scene->clear();
        QPixmap pix(":/new/prefix1/resources/movie.svg");        
        m_scene->addPixmap(pix);
        int w=m_sequence->movieResolution().width();
        int h=m_sequence->movieResolution().height();
        QString str=QString(tr("Movie Resolution : %1 x %2")).arg(w).arg(h);

        statusBar()->showMessage(str, 5000);

        m_engine->setExportMovie(fileName);
        m_engine->start();
        m_engine->resetExportMovie();
        m_scene->clear();

        ui->stopButton->setEnabled(false);
        ui->actionStop->setEnabled(false);

        slideShowProgress(0);
        //ui->timeBar->setValue(0);
        //ui->lcdNumber->display(0);
        ///ui->totalDurationTime->display(0);
    }
}



void MainWindow::manageSoundtracks()
{
    soundtracksDialog dialog;
    dialog.setModelData(m_sequence);
    dialog.exec();
}



void MainWindow::modelChanged(QModelIndex topLeft,QModelIndex bottomRight)
{
    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);

    //ui->nSlides->setText(QString("%1 ").arg(m_sequence->rowCount()));

    QString rows=QString(tr("Slides: %1, ")).arg(m_sequence->rowCount());

    int audioTracks=m_sequence->soundtracks().count();
    QString track;
    if(audioTracks>0)
        track=QString(tr("Audio Track: %1, ").arg(audioTracks));
    else
        track=QString(tr("No Audio Track, "));


    int msDuration=m_sequence->duration();
    int cent=msDuration/10 %100;
    int seconds=msDuration/1000 %60;
    int minutes=msDuration/60000 %60;
    int hour=msDuration/3600000 %60;
    QString stdTime=QString(tr("Duration %1:%2:%3.%4")).arg(hour).arg(minutes).arg(seconds).arg(cent);

    QString complete=rows;
    complete.append(track);
    complete.append(stdTime);

    ui->infoString->setText(complete);

}

