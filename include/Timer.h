#ifndef TIMER_H
#define TIMER_H
#include <sys/types.h>
#include <SDL.h>
class Timer
{
    public:
        Timer();
        virtual ~Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        Uint32 getTicks();
        bool isStarted();
        bool isPaused();
    protected:

    private:
        Uint32 mStartTicks;
        Uint32 mPausedTicks;

        bool mPaused;
        bool mStarted;
};

#endif // TIMER_H
