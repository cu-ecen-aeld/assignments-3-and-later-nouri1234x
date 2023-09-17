#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data *t_param = (struct thread_data *) thread_param;
    usleep (t_param->wait_to_obtain_ms *1000);
     int rc=pthread_mutex_lock(t_param->mutex);
     if (rc != 0) {
    perror("Failed thread  lock, error was");
     t_param->thread_complete_success = false;
     return thread_param;}
    
    usleep (t_param->wait_to_release_ms *1000);
    
    rc=pthread_mutex_unlock(t_param->mutex);
     if (rc != 0) {
     perror("Failed thread  unlock, error was");
     t_param->thread_complete_success = false;
     return thread_param;}
    t_param->thread_complete_success = true;
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
     struct thread_data *params;
     params=calloc(1,(sizeof(struct thread_data )));

     //memset(&params,0,sizeof(struct thread_data));
     params->wait_to_obtain_ms = wait_to_obtain_ms;
     params->wait_to_release_ms=wait_to_release_ms;
     params->mutex=mutex;
     DEBUG_LOG("Main thread, PID %d TID %d", getpid(), (pid_t)syscall(SYS_gettid));

     if ( thread == NULL ) {
                ERROR_LOG("Failed to create thread");
                return false;
            } 
            else {
                int rc = pthread_create(thread,NULL,threadfunc,params);
                if ( rc != 0 ) {
                    ERROR_LOG("Failed to create thread");
                    return false;
                }
                printf("Started thread %ld with id \n",*thread);
            }
   
     
    return true;
}
