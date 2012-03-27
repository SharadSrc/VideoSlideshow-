#ifndef SOUNDTRACKSDIALOG_H
#define SOUNDTRACKSDIALOG_H

#include <QtGui>
#include "sequencemodel.h"

namespace Ui {
    class soundtracksDialog;
}

class soundtracksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit soundtracksDialog(QWidget *parent = 0);
    ~soundtracksDialog();
    void setModelData(sequenceModel *model);

public slots:
    void goUpSlot();
    void goDownSlot();
    void removeSlot();
    void addSlot();    
    void arrangeTimeSlot();


private:        
    void trackStats();
    Ui::soundtracksDialog *ui;
    sequenceModel *m_model;
    int mSTotalDuration;
};

#endif // SOUNDTRACKSDIALOG_H
