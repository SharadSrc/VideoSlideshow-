#ifndef MOVIEPROPERTIESDIALOG_H
#define MOVIEPROPERTIESDIALOG_H

#include <QDialog>
#include "sequencemodel.h"

namespace Ui {
    class moviePropertiesDialog;
}

class moviePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit moviePropertiesDialog(QWidget *parent = 0);
    ~moviePropertiesDialog();
    void setModelData(sequenceModel *model);


public slots:
    void applySlot();

private:
    QSize resolutionFromIndex(int index);
    int indexFromResolution(QSize size);
    Ui::moviePropertiesDialog *ui;
    sequenceModel *m_model;
};

#endif // MOVIEPROPERTIESDIALOG_H
