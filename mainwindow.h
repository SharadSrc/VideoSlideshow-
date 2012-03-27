#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "sequencemodel.h"
#include "delegate.h"
#include "pixmap.h"
#include "slideshowengine.h"
#include <QtGui>


//#include <phonon/mediaobject.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //void timerEvent(QTimerEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    void modelChanged(QModelIndex,QModelIndex);
    void listClicked(const QModelIndex & index);
    void listDoubleClicked(const QModelIndex & index);
    void listContextMenuRequested(QPoint pos);
    void dirViewClickSlot(QModelIndex);
    void dirViewDoubleClickSlot(QModelIndex);
    void createEditor();
    void startSlideShowEngine();
    void pauseSlideShowEngine();
    void stopSlideShowEngine();
    void fileNewSlot();
    void fileOpenSlot();
    void fileCloseSlot();
    void fileSaveSlot();
    void fileSaveAsSlot();
    void exitSlot();
    void removeItemInList();
    void exportToMovie();
    void movieOptionsSlot();
    void manageSoundtracks();
    void slideShowProgress(int time);
    void endSlideShow();


private:
    void createListContextMenu();
    void writeSettings();
    void readSettings();

    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Pixmap *m_item1;
    sequenceModel *m_sequence;
    QFileSystemModel m_FileSystemModel;
    QMenu *m_listContextMenu;
    QAction *m_nodePropertyAct,*m_removeNodeAct;//,*insertBeforeAct,*m_insertAfterAct;
    delegate *m_delegate;
    slideShowEngine *m_engine;   
    int m_timerId;
    QString m_slideShowFilePath;
    //Phonon::MediaObject *mediaObject;
    //ImageLoader loader;
    //QThread thread;

};

#endif // MAINWINDOW_H
