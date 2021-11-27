#ifndef TIMER_H
#define TIMER_H

#include <QTimer>


// Just for convenience
class Timer: public QTimer
{
public:
    Timer(QObject *parent, int timeout, std::function<void(void)> functor);
};


#endif // TIMER_H
