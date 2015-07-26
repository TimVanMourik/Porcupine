#ifndef HIDER_H
#define HIDER_H

#include <QEvent>
#include <QObject>
#include <QWidget>

#include <iostream>
class Hider : public QObject
{
    Q_OBJECT
public:
    //
    Hider(
            QObject * parent = 0
            ) :
        QObject(parent)
    {}
    //
    bool eventFilter(
            QObject *, QEvent * ev
            )
    {
        return ev->type() == QEvent::Paint;
    }
    //
    void hide(
            QWidget* _widget
            )
    {
        _widget->installEventFilter(this);
        _widget->update();
    }
    //
    void unhide(
            QWidget* _widget
            )
    {
        _widget->removeEventFilter(this);
        _widget->update();
    }
    //
    Q_SLOT void hideWidget(
            QObject*
            )
    {
        QObject * s = sender();
        if (s->isWidgetType())
        {
            hide(qobject_cast<QWidget*>(s));
        }
    }
};

#endif // HIDER_H
