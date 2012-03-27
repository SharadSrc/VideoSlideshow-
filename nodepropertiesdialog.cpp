

#include <QtGui>
#include "nodepropertiesdialog.h"
#include "ui_nodepropertiesdialog.h"

nodePropertiesDialog::nodePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nodePropertiesDialog)
{
    ui->setupUi(this);
    connect(ui->applyButton,SIGNAL(released()),this,SLOT(applySlot()));
    connect(ui->applyAllButton,SIGNAL(released()),this,SLOT(applyAllSlot()));
    connect(ui->backButton,SIGNAL(released()),this,SLOT(backPageSlot()));
    connect(ui->forwardButton,SIGNAL(released()),this,SLOT(forwardPageSlot()));

    propertyMap["pos"]=0;
    propertyMap["rotation"]=1;
    propertyMap["scale"]=2;
    propertyMap["opacity"]=3;



}

nodePropertiesDialog::~nodePropertiesDialog()
{
    delete ui;
}



void nodePropertiesDialog::setEditorData(const QModelIndex &index)
{
node currentItem;

    m_currentIindex=index;
    QVariant val=index.data(Qt::UserRole);
    currentItem=val.value<node>();
    ui->imagePreview->setPixmap(currentItem.nodePixmap());
    ui->imagePath->setText(currentItem.nodePath());
    ui->width->setText(QString("%1").arg(currentItem.pixmapSize().width()));
    ui->height->setText(QString("%1").arg(currentItem.pixmapSize().height()));
    ui->imageName->setText(currentItem.nodeName());

    effect e=currentItem.enterEffect();

    ui->enterStartVal->setText(QString("%1").arg(e.startValue()));
    ui->enterEndVal->setText(QString("%1").arg(e.endValue()));
    ui->enterStartPointFX->setText(QString("%1").arg(e.startPointF().x()));
    ui->enterStartPointFY->setText(QString("%1").arg(e.startPointF().y()));
    ui->enterEndPointFX->setText(QString("%1").arg(e.endPointF().x()));
    ui->enterEndPointFY->setText(QString("%1").arg(e.endPointF().y()));
    ui->enterDuration->setText(QString("%1").arg(e.duration()));
    ui->enterDirection->setCurrentIndex(e.direction());
    ui->enterEasingCurve->setCurrentIndex(e.easingCurve());
    ui->enterProperty->setCurrentIndex(propertyMap.value(e.effectType()));

    e=currentItem.displayEffect();

    ui->displayStartVal->setText(QString("%1").arg(e.startValue()));
    ui->displayEndVal->setText(QString("%1").arg(e.endValue()));
    ui->displayStartPointFX->setText(QString("%1").arg(e.startPointF().x()));
    ui->displayStartPointFY->setText(QString("%1").arg(e.startPointF().y()));
    ui->displayEndPointFX->setText(QString("%1").arg(e.endPointF().x()));
    ui->displayEndPointFY->setText(QString("%1").arg(e.endPointF().y()));
    ui->displayDuration->setText(QString("%1").arg(e.duration()));
    ui->displayDirection->setCurrentIndex(e.direction());
    ui->displayEasingCurve->setCurrentIndex(e.easingCurve());
    ui->displayProperty->setCurrentIndex(propertyMap.value(e.effectType()));

    e=currentItem.exitEffect();

    ui->exitStartVal->setText(QString("%1").arg(e.startValue()));
    ui->exitEndVal->setText(QString("%1").arg(e.endValue()));
    ui->exitStartPointFX->setText(QString("%1").arg(e.startPointF().x()));
    ui->exitStartPointFY->setText(QString("%1").arg(e.startPointF().y()));
    ui->exitEndPointFX->setText(QString("%1").arg(e.endPointF().x()));
    ui->exitEndPointFY->setText(QString("%1").arg(e.endPointF().y()));
    ui->exitDuration->setText(QString("%1").arg(e.duration()));
    ui->exitDirection->setCurrentIndex(e.direction());
    ui->exitEasingCurve->setCurrentIndex(e.easingCurve());
    ui->exitProperty->setCurrentIndex(propertyMap.value(e.effectType()));

}


void nodePropertiesDialog::applyAllSlot()
{
   QModelIndex m_saveCurrentIindex;
   m_saveCurrentIindex=m_currentIindex;
   for(int i=0;i<m_model->rowCount();i++)
   {
        m_currentIindex=m_model->index(i);
        applySlot();
   }
   m_currentIindex=m_saveCurrentIindex;
}



void nodePropertiesDialog::applySlot()
{
    QString str1,str2;
    effect e;    
    QAbstractAnimation::Direction direction;
    QEasingCurve::Type easing;
    node currentItem;

    QVariant val=m_currentIindex.data(Qt::UserRole);
    currentItem=val.value<node>();

    str1=ui->enterStartVal->text();
    e.setStartValue(qreal(str1.toDouble()));

    str1=ui->enterEndVal->text();
    e.setEndValue(qreal(str1.toDouble()));

    str1=ui->enterStartPointFX->text();
    str2=ui->enterStartPointFY->text();
    e.setStartPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toFloat())));

    str1=ui->enterEndPointFX->text();
    str2=ui->enterEndPointFY->text();
    e.setEndPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toDouble())));

    str1=ui->enterDuration->text();
    e.setDuration(str1.toInt());

    str1=ui->enterDirection->currentIndex();

    direction=(QAbstractAnimation::Direction)str1.toInt();
    e.setDirection(direction);

    easing=(QEasingCurve::Type)ui->enterEasingCurve->currentIndex();
    e.setEasingCurve(easing);

    str1=ui->enterProperty->currentText();
    e.setEffectType(str1);

    currentItem.setEnterEffect(e);

    str1=ui->displayStartVal->text();
    e.setStartValue(qreal(str1.toDouble()));
    str1=ui->displayEndVal->text();
    e.setEndValue(qreal(str1.toDouble()));

    str1=ui->displayStartPointFX->text();
    str2=ui->displayStartPointFY->text();
    e.setStartPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toFloat())));

    str1=ui->displayEndPointFX->text();
    str2=ui->displayEndPointFY->text();
    e.setEndPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toDouble())));

    str1=ui->displayDuration->text();
    e.setDuration(str1.toInt());

    str1=ui->displayDirection->currentIndex();

    direction=(QAbstractAnimation::Direction)str1.toInt();
    e.setDirection(direction);

    easing=(QEasingCurve::Type)ui->displayEasingCurve->currentIndex();
    e.setEasingCurve(easing);

    str1=ui->displayProperty->currentText();
    e.setEffectType(str1);

    currentItem.setDisplayEffect(e);

    str1=ui->exitStartVal->text();
    e.setStartValue(qreal(str1.toDouble()));
    str1=ui->exitEndVal->text();
    e.setEndValue(qreal(str1.toDouble()));

    str1=ui->exitStartPointFX->text();
    str2=ui->exitStartPointFY->text();
    e.setStartPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toFloat())));

    str1=ui->exitEndPointFX->text();
    str2=ui->exitEndPointFY->text();
    e.setEndPointF(QPointF(qreal(str1.toDouble()),qreal(str2.toDouble())));

    str1=ui->exitDuration->text();
    e.setDuration(str1.toInt());

    str1=ui->exitDirection->currentIndex();

    direction=(QAbstractAnimation::Direction)str1.toInt();
    e.setDirection(direction);

    easing=(QEasingCurve::Type)ui->exitEasingCurve->currentIndex();
    e.setEasingCurve(easing);

    str1=ui->exitProperty->currentText();
    e.setEffectType(str1);

    currentItem.setExitEffect(e);

    val.setValue(currentItem);
    m_model->setData(m_currentIindex,val,Qt::EditRole);


}



void nodePropertiesDialog::backPageSlot()
{
 int index=ui->listWidget->currentRow();
 if(index>0)
    ui->listWidget->setCurrentRow(index-1);


}

void nodePropertiesDialog::forwardPageSlot()
{
    int index=ui->listWidget->currentRow();
    if(index<ui->listWidget->count()-1)
       ui->listWidget->setCurrentRow(index+1);
}
