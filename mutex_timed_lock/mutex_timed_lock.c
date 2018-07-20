//From site http://tuxthink.blogspot.com/2013/01/using-pthreadmutextimedlock-in-linux.html

#include<unistd.h>
#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define perror(s) printf("\n" s "\n");

pthread_mutex_t mutex1;


void  *func1(){

        printf("I'am func1\n");

        pthread_mutex_lock(&mutex1);
        printf("func1: lock acquired, now wait for 10sec to let other threads to run\n");
        sleep(10);
        printf("func1: Finished 10sec wait\n");
        pthread_mutex_unlock(&mutex1);
        return NULL;
}

void  *func2() {

        printf("I'am func2\n");
        struct timespec wait;

        clock_gettime(CLOCK_REALTIME, &wait);

        wait.tv_sec+= 5;

        printf("func2: lock to be acquired, max wait is 5 sec\n");


        if(pthread_mutex_timedlock(&mutex1,&wait))
        {
             perror("func2: Wait of 5 sec timed out");
             return NULL;
        }
        else
        {
             printf("func2: lock acquired with no interaction with func 1\n");
        }

        pthread_mutex_unlock(&mutex1);

        return NULL;
}


int main() {

        pthread_t thread1,thread2;

        printf("\nCreating threads\n");

        if (pthread_create(&thread1,NULL,func1,NULL))
        {
                perror("Unable to create thread1");
        }
        else
        {
                printf("main: give the possibility to func1 to run if it still didn't waiting for 1 sec\n");
                sleep(1);


                if (pthread_create(&thread2,NULL,func2,NULL))
                {
                        perror("Unable to  create thread2");
                }
                else
                {
                        printf("main: func2 in running or ready state\n");

                }
        }


        pthread_exit(0);

}

