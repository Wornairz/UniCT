#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void (*timer_func_handler_pntr)(void);

struct itimerval timervalue;

struct sigaction new_handler, old_handler;

void timer_sig_handler(int);

void timer_handler(void);

int start_timer(int mSec, void (*timer_func_handler)(void))
{
    timer_func_handler_pntr = timer_func_handler;

    timervalue.it_interval.tv_sec = mSec / 1000;
    timervalue.it_interval.tv_usec = (mSec % 1000) * 1000;
    timervalue.it_value.tv_sec = mSec / 1000;
    timervalue.it_value.tv_usec = (mSec % 1000) * 1000;
    if (setitimer(ITIMER_REAL, &timervalue, NULL))
    {
        printf("\nsetitimer() error\n");
        return (1);
    }

    new_handler.sa_handler = &timer_sig_handler;
    new_handler.sa_flags = SA_NOMASK;
    if (sigaction(SIGALRM, &new_handler, &old_handler))
    {
        printf("\nsigaction() error\n");
        return (1);
    }

    return (0);
}

void timer_sig_handler(int arg)
{
    timer_func_handler_pntr();
}

void stop_timer(void)
{
    timervalue.it_interval.tv_sec = 0;
    timervalue.it_interval.tv_usec = 0;
    timervalue.it_value.tv_sec = 0;
    timervalue.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &timervalue, NULL);

    sigaction(SIGALRM, &old_handler, NULL);
}














int var = 0;

int main(void)
{

    if (start_timer(10000, &timer_handler))
    {
        printf("\n timer error\n");
        return (1);
    }

    printf("\npress ctl-c to quit.\n");

    while (1)
    {
        if (var > 5)
        {
            break;
        }
    }

    stop_timer();

    return (0);
}

void timer_handler(void)
{
    printf("timer: var is %i\n", var++);
}
