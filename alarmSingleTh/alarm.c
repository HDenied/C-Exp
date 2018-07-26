#include<stdio.h>
#include<time.h>
#include<signal.h>
#include<errno.h>
#include<stdlib.h>
#include <unistd.h>

#define TIMEOUT_SEC 5

typedef unsigned int uint32_t;

static pthread_t th1;

static struct timespec timeout={TIMEOUT_SEC,0};

/*NOTE: this is AS-safe, not MT-safe, therefore can't be used in a system which uses a multithreaded environment, it would give an undefined behaviour*/
static volatile sig_atomic_t timestamp;

static void * thFunc(void *arg);

static void alarm_isr(int sig);

static void DBG_Lock(const char *filename, const char* funcname, unsigned int line);

int main()
{
    static struct timespec timeLeft={0,0};

    //1 - Configuring the alarm
    signal(SIGALRM, alarm_isr);

    printf("Arming the alarm for %usec\n",timeout.tv_sec);
    //2 - Enabling the alarm
    alarm(timeout.tv_sec);

    //Sleep in order to trigger the alarm for a time longer than the timer
    timeout.tv_sec+=2;

    if(!clock_nanosleep(CLOCK_MONOTONIC, 0, &timeout, &timeLeft))
    {
        printf("Timeout expired, isr has not been triggered, timeleft is sec=%d msec=%d\n", timeLeft.tv_sec, timeLeft.tv_nsec/1000000);
    }
    else
    {
        printf("Extended timeout not expired, isr has been triggered, timeleft is sec=%d msec=%d\n", timeLeft.tv_sec, timeLeft.tv_nsec/1000000);
    }

    return 0;

}



static void alarm_isr(int sig)
{
    printf("Alarm timeout expired\n");
}
