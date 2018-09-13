/*
    Parallization for histogram
    Author: Gahan Saraiya
    website: gahan9.github.io
    code: https://github.com/gahan9/CA_lab/blob/master/parallel_programming/histogram_loop_splitting.c
    Date : 13/09/2018
*/

#include <stdio.h>  // standard input output library
#include <stdlib.h>  // standard input output library
#include <stdarg.h>  // for utilities like va_list used in write_log function
#include <string.h>  
#include <sys/wait.h>  // to invoke wait() explicitly
#include <unistd.h>  // to invoke fork() explicitly
// libraries for semaphores and inter process communication
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define DEBUG 0
#define MAXLEN 1000
#define MAXBINS 10

int write_log(const char *format, ...) {
    if(DEBUG) {
        va_list args;
        va_start (args, format);
        vprintf(format, args);
        va_end (args);
    }
}

void min_max(float *array, int n, float *array_max, float *array_min) {
    write_log("calculating min and max of array\n");
	int i;
	*array_max = *array;
	*array_min = *array;
	for (i=0;i<n;i++)
	{
		if (array[i] > *array_max)
			*array_max = array[i];
		if (array[i] < *array_min)
			*array_min = array[i];
	}
}


int process_fork(int number_of_process) {
	int j;
	for(int i=1; i<number_of_process; i++) {
		if((j=fork()) == 0)
			return i;  // return child process number if created successfully
		if(j == -1)
			write_log("Unable to fork proc. %d\n",i);
	}
	return 0;
}

int process_join(int process_id, int number_of_process) {
	if(process_id == 0) {
		for(int i=1; i<number_of_process; i++)
			wait(0);
		return 0;  // wait till execution of parent process completed.
	}
	write_log("Process %d\n", process_id);
	exit(0);
}


void spin_lock_init(int* lok, int* condition) {
	/*
	IPC_PRIVATE: Interprocess Communication within block
	0666|IPC_CREAT: A new set of nsems semaphores is created with permission 0666
	read in detail at https://linux.die.net/man/2/semget
	*/
	int control, lok1;
	// semget(key_t key, int nsems, int semflg);
	lok1 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);  // get semaphore set identifier associated with the argument key IPC_PRIVATE or create 
	*lok = lok1;
	if (*condition == 0)
		control = 1;
	else
		control = 0;

	// semctl(int semid, int semnum, int cmd, ...);
	semctl(*lok, 0, SETVAL, control);  // Semaphore control operation.
	// performs the control operation specified by cmd on the semaphore set 
}

void spin_lock(int *lok) {
    struct sembuf operations;
	operations.sem_num=0;
	operations.sem_op=-1;
	operations.sem_flg=0;
	semop(*lok, &operations, 1);
}

void spin_unlock(int *lok) {
    struct sembuf operations;
	operations.sem_num=0;
	operations.sem_op=1;
	operations.sem_flg=0;
	semop(*lok, &operations, 1);
}

char * shared(int size, int *shmid) {
	*shmid = shmget(IPC_PRIVATE, size, 0666|IPC_CREAT);  // Get shared memory segment
	return(shmat(*shmid, 0, 0));  // Attach shared memory segment.
}


/* Main Program */
int main() {
	// Declaration
	int *shmid, i, *lock, pid, no_process=MAXBINS;
	int *cond, *histogram,bin;
	float *array_max, *array_min, *array, bin_size;

	array_max = (float*) malloc(sizeof(float));
	array_min = (float*) malloc(sizeof(float));
	shmid = (int*) malloc(sizeof(int));

	cond =(int*) malloc(sizeof(int));
	*cond = 0;

	// generate array in shared memory with random number
	array = (float*)shared(MAXLEN*sizeof(float), shmid);
	for (i=0; i<MAXLEN; i++)
		array[i]= rand() % MAXBINS;

	// initialize histogram array in shared memory with all 0s
	histogram = (int*)shared(MAXBINS*sizeof(int), shmid);
	for (i=0; i<MAXBINS; i++)
		histogram[i]=0;
	
	lock = (int *)shared (4, shmid);
	min_max(array, MAXLEN, array_max, array_min); // get min and max of array

	bin_size = (*array_max - *array_min) / MAXBINS; // calculate bin size

	// Loop Splitting based on number of process
	pid = process_fork(no_process);
	for(i=pid; i<MAXLEN; i+=no_process){
		if (array[i] > *array_max)
			*array_max = array[i];
		bin = (int) (abs(array[i] - *array_min)/bin_size);
		if (bin > MAXBINS)
			bin = MAXBINS;
		// Locking mechanism to prevent WAW Hazard
		spin_lock(lock);
		histogram[bin] += 1;  // critical section
		spin_unlock(lock);
	}

	/* What else?? can't leave like that.. let's join process */
	process_join(pid, no_process);
	for(int x=0; x<MAXBINS; x++){
		for (int y=0; y<histogram[x]; y++)
			printf("#");
		printf(" %d \n", histogram[x]);
	}
	printf("\n");
	return 1;
}
