#include "Timer.h"

double Timer::MICRO = 1000000.0;

Timer::Timer( void )
{

#ifdef WINDOWS

    QueryPerformanceFrequency(&_freq);
    _startCount.QuadPart = 0;
    _endCount.QuadPart   = 0;

#else

    _startCount.tv_sec = 0;
    _startCount.tv_usec = 0;
    _endCount.tv_sec = 0;
    _endCount.tv_usec = 0;

#endif 

    _stopped = false;
    _startTimeMicro = 0;
    _endTimeMicro   = 0;

}

Timer::~Timer( void )
{
}

string Timer::toString( void ) const
{
    return "Timer";
}

void Timer::start( void )
{
    _stopped = false;

#ifdef WINDOWS

    QueryPerformanceCounter(&_startCount);

#else

    gettimeofday(&_startCount, nullptr);

#endif

}

void Timer::stop( void )
{
    _stopped = true;

#ifdef WIN32

    QueryPerformanceCounter(&_endCount);

#else

    gettimeofday(&_endCount, nullptr);

#endif

}

double Timer::getElapsedMicro( void )
{

#ifdef WINDOWS

    if (!_stopped)
        QueryPerformanceCounter(&_endCount);

    _startTimeMicro = _startCount.QuadPart * (MICRO / _freq.QuadPart);
    _endTimeMicro   = _endCount.QuadPart * (MICRO / _freq.QuadPart);

#else

    if (!_stopped)
        gettimeofday(&_endCount, nullptr);

    _startTimeMicro = (_startCount.tv_sec * MICRO) + _startCount.tv_usec;
    _endTimeMicro   = (_endCount.tv_sec * MICRO) + _endCount.tv_usec;

#endif

    return _endTimeMicro - _startTimeMicro;
}

double Timer::getElapsedMilli( void )
{
    return getElapsedMicro() / 1000.0;
}

double Timer::getElapsed( void )
{
    return getElapsedMilli() / 1000.0;
}

void Timer::sleepUntilElapsed( double millis )
{

    double timeToSleep;

#ifdef WINDOWS

    LARGE_INTEGER 
        currentTime,
        lastTime;

    QueryPerformanceCounter( &currentTime );
    timeToSleep = millis - calcDiffMillis( _startCount, currentTime );

#else

    timeval
        currentTime,
        lastTime;

    gettimeofday(&currentTime, nullptr);
    timeToSleep = millis - 

#endif

    while ( timeToSleep > 0.0 )
    {
        double timeElapsed;
        lastTime = currentTime;

#ifdef WINDOWS

        QueryPerformanceCounter( &currentTime );
        timeElapsed = calcDiffMillis( lastTime, currentTime );

#else

        gettimeofday(&_endCount, nullptr);
        timeElapsed = calcDiffMillis( lastTime, currentTime );

#endif
        timeToSleep -= timeElapsed;

        if( timeToSleep > 10.0 )
        {
            Sleep(10);
        }
    }
}

#ifdef WINDOWS

double Timer::calcDiffMillis( LARGE_INTEGER from, LARGE_INTEGER to ) const
{
    double difference = (double)(to.QuadPart - from.QuadPart) * (MICRO / _freq.QuadPart);

    return difference / 1000.0;
}

#else

double Timer::calcDiffMillis( timeval from, timeval to ) const
{
    double 
        start = (from.tv_sec * MICRO) + from.tv_usec,
        end   = (to.tv_sec * MICRO) + to.tv_usec;

    return (start - end) / 1000.0;
}

#endif
