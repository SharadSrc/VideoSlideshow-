#ifndef EFFECT_H
#define EFFECT_H

#include <QtGui>



class effect
{
public:

    effect();
    void setEffectType(QString effect){m_effect=effect;};
    QString effectType(){return m_effect;};

    void setStartPointF(QPointF pointF){m_startPointF=pointF;};
    QPointF startPointF(){return m_startPointF;};

    void setEndPointF(QPointF pointF){m_endPointF=pointF;};
    QPointF endPointF(){return m_endPointF;};

    void setStartValue(qreal startValue){m_startValue=startValue;};
    qreal startValue(){return m_startValue;};

    void setEndValue(qreal endValue){m_endValue=endValue;};
    qreal endValue(){return m_endValue;};

    void setDuration(int duration){m_duration=duration;};
    int duration(){return m_duration;};

    void setDirection(QAbstractAnimation::Direction direction) {m_direction=direction;};
    QAbstractAnimation::Direction direction(){return m_direction;};

    void setEasingCurve(QEasingCurve::Type curve) {m_easingCurve=curve;};
    QEasingCurve::Type easingCurve(){return m_easingCurve;};


private:
    QString m_effect;
    int m_duration;
    QAbstractAnimation::Direction m_direction;
    qreal m_startValue,m_endValue;
    QPointF m_startPointF,m_endPointF;
    QEasingCurve::Type m_easingCurve;

};


 QDataStream &operator<<(QDataStream &out, effect &effectData);
 QDataStream &operator>>(QDataStream &in, effect &effectData);



Q_DECLARE_METATYPE(effect)

#endif // EFFECT_H
