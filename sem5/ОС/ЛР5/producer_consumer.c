#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

const int N = 10;
const int PERM = S_IRWXU | S_IRWXG | S_IRWXO;

int* shared_pos_producer;
int* shared_pos_consumer;
int* shared_buffer;
int ctl_sb, ctl_se, ctl_sf;

struct sembuf producer_start[2] = {{1, -1, 0}, {2, -1, 0}};
struct sembuf producer_stop[2] =  {{0,  1, 0}, {2, 1, 0}};
struct sembuf consumer_start[2] = {{0, -1, 0}, {2, -1, 0}};
struct sembuf consumer_stop[2] =  {{1,  1, 0}, {2, 1, 0}};

void producer(int semid, int index)
{
	sleep(rand() % 3);
	if (semop(semid, producer_start, 2) == -1)
	{
		perror("Semop producer_start!");
		exit(1);
	}
	shared_pos_producer = shared_pos_producer + index;
	*shared_pos_producer = index;
	printf("producer set %d to %ld pos\n", *shared_pos_producer, shared_pos_producer - shared_buffer);
	if (semop(semid, producer_stop, 2) == -1)
	{
		perror("Semop producer_stop!");
		exit(1);
	}
}


void consumer(int semid, int index)
{
	sleep(rand() % 5);
	if (semop(semid, consumer_start, 2) == -1)
	{
			perror("Semop consumer_start!");
			exit(1);
	}
	shared_pos_consumer = shared_pos_consumer + index;
	printf("consumer read %d from %d pos\n", *shared_pos_consumer, index);
	if (semop(semid, consumer_stop, 2) == -1)
	{
		perror("Semop consumer_stop!");
		exit(1);
	}
}

int main()
{
	int shmid, semid;
	int parent_pid = getpid();
	printf("Parent pid: %d\n", parent_pid);
	
	// Creating shared memory
	if ((shmid = shmget(IPC_PRIVATE, N * sizeof(int), IPC_CREAT | PERM)) == -1)
	{
		perror("Unable to create shared memory!\n");
		exit(1);
	}

	shared_buffer = shmat(shmid, 0, 0);
	shared_pos_producer = shared_pos_consumer = shared_buffer;
	if (*shared_pos_producer == -1)
	{
		perror("Can't attach memory!\n");
		exit(1);
	}

	// Creating semaphore
	if ((semid = semget(IPC_PRIVATE, 3, IPC_CREAT | PERM)) == -1)
	{
		perror("Unable to create semaphore!\n");
		exit(1);
	}
	
	// Creating control semaphore
	if ((ctl_sb = semctl(semid, 0, SETVAL, 0)) == -1)
	{
		perror("Unable to set control semaphore! (full)\n");
		exit(1);
	}
	else if ((ctl_se = semctl(semid, 1, SETVAL, N)) == -1)
	{
		perror("Unable to set control semaphore! (empty)\n");
		exit(1);
	}
	else if ((ctl_sf = semctl(semid, 2, SETVAL, 1)) == -1)
	{
		perror("Unable to set control semaphore! (binary)\n");
		exit(1);
	}

	pid_t pid[N];
	int flag = 1;
	for (int i = 0, j = 0, c = 0; i < N; i++)
	{
		if (flag)
		{
			if (i % 2)
			{
				pid[i] = fork();
				if (pid[i] == -1)
				{
					perror("Unable to fork! (i)");
					exit(1);
				}
				if (pid[i] == 0)
				{
					printf("forked consumer = %d\n", getpid());
					flag = 0;
					consumer(semid, c);
				}
				else
				{
					// printf("forked consumer = %d\n", getpid());
				}
				c++;
				
			}
			else 
			{
				pid[i] = fork();
				if (pid[i] == -1)
				{
					perror("Unable to fork! (i)");
					exit(1);
				}
				if (pid[i] == 0)
				{
					printf("forked producer = %d\n", getpid());
					flag = 0;
					producer(semid, j);
				}
				else
				{
					// printf("forked producer = %d\n", getpid());
				}
				j++;
			}
		}	
	}
	for (int h = 0; h < N / 2; h++)
		printf("%d ", *(shared_buffer + h));
	printf("\n");
	if (flag) 
	{
		int status, child;
		for (int i = 0; i < N; i++)
		{
			child = wait(&status);
			printf("Child has finished: PID = %d CODE = %d\n", child, WEXITSTATUS(status));
		}

		if (shmdt(shared_buffer) == -1) 
		{
			perror( "Detach memory error!\n" );
			exit( 1 );
		}
	}
	return 0;
}
