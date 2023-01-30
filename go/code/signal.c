#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>


struct sigaction act;

void sighandler(int signum, siginfo_t *info, void *ptr)
{
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);
	    printf("Received signal %d, thread id: %d, time: %d\n", signum,(int)(pthread_self()), (int)spec.tv_nsec);
	    printf("Signal originates from process %lu\n",
				        (unsigned long)info->si_pid);
}

void* thread1(void* ptr){
	printf("thread1 id: %d \n", getpid());
	while(1){}
}

int main()
{
	    printf("I am %lu\n", (unsigned long)pthread_self());

	    pthread_t thread;
	    pthread_create(&thread,  NULL, thread1, NULL);

        struct itimerval new_val;
        new_val.it_value.tv_sec = 0;
        new_val.it_value.tv_usec = 1;
        new_val.it_interval.tv_sec = 0;
        new_val.it_interval.tv_usec = 100000;
        setitimer(ITIMER_PROF, &new_val, NULL);

	    memset(&act, 0, sizeof(act));
	    act.sa_sigaction = sighandler;
	    act.sa_flags = SA_SIGINFO;
	    sigaction(SIGPROF, &act, NULL);

			        // Waiting for CTRL+C...
				//     sleep(100);
	    while(1){}		    
	    return 0;
}		
