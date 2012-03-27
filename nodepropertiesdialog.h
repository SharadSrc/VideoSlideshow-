#ifndef NODEPROPERTIESDIALOG_H
#define NODEPROPERTIESDIALOG_H

#include "sequencemodel.h"
#include "node.h"
#include <QtGui>


namespace Ui {
    class nodePropertiesDialog;
}

class nodePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit nodePropertiesDialog(QWidget *parent = 0);
    ~nodePropertiesDialog();
    void setEditorData(const QModelIndex &index);
    void setModelData(sequenceModel *model){m_model=model;};
    //void allowImageSelection(bool enable);

public slots:
    void applySlot();
    void applyAllSlot();
    void backPageSlot();
    void forwardPageSlot();
    //void chooseImageFile();

private:
    Ui::nodePropertiesDialog *ui;
    //QMap<int, int> easingCurveMap;
    QMap<QString, int> propertyMap;    
    sequenceModel *m_model;
    QModelIndex m_currentIindex;


};

#endif // NODEPROPERTIESDIALOG_H
