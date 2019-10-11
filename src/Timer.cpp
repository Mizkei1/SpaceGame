#include "Timer.h"
Timer::Timer()
{
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

Timer::~Timer()
{
    //dtor
}

void Timer::start() {
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::stop() {
    mStarted = false;
    mPaused = true;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::pause() {

    if (mStarted && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}
    void Timer::unpause() {

    if (mStarted && mPaused) {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mStartTicks;
        mPausedTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;
    if(mStarted) {
        if(mPaused) {
            time = mPausedTicks;
        }
        else {
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool Timer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool Timer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}
