#include <QtGui>
#include "effect.h"

effect::effect()
{
    setEffectType("opacity");
    setStartValue(1.0);
    setEndValue(1.0);
    setDuration(10);
    setDirection(QAbstractAnimation::Forward);
    m_easingCurve=QEasingCurve::Linear;
}


// Paolo: dava errore con const &effectData ora non più. Perchè?
QDataStream &operator<<(QDataStream &out, effect &effectData)
{
    out << effectData.effectType() << effectData.startPointF() << effectData.endPointF();
    out << qreal(effectData.startValue()) << qreal(effectData.endValue()) << qint32(effectData.duration());
    out << quint32(effectData.direction());
    out << quint32(effectData.easingCurve());
    return out;
}

QDataStream &operator>>(QDataStream &in, effect &effectData)
{
QString effectType;
qreal startVal,endVal;
quint32 durationVal,directionVal,easingVal;
QEasingCurve::Type easingCurve;
QAbstractAnimation::Direction direction;
QPointF startPointF,endPointF;


    in >> effectType >> startPointF >> endPointF >> startVal  >> endVal >> durationVal >> directionVal >> easingVal;
    effectData.setEffectType(effectType);
    effectData.setStartPointF(startPointF);
    effectData.setEndPointF(endPointF);
    effectData.setStartValue(startVal);
    effectData.setEndValue(endVal);
    effectData.setDuration(durationVal);

    direction=(QAbstractAnimation::Direction) directionVal;
    effectData.setDirection(direction);

    easingCurve=(QEasingCurve::Type) easingVal;
    effectData.setEasingCurve(easingCurve);

    return in;
}

