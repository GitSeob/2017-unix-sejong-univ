#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <signal.h>

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

struct buffer{
	int p_count;
	int c_count;
	int data;
	int flag;
};

void producer(int semid, struct buffer *buf);
void consumer(int semid, struct buffer *buf);
void sem_op(int semid, int semnum, int sem_op);

#define N 10

int main(int argn, char **argv){
	ushort buf[3] = {0,N,1};
	int semid, shmid, id, i;
	key_t semkey, shmkey;
	struct buffer *shmbuf;
	//struct sembuf p_buf;
	union semun arg;
	//char op1 = 'P', op2 = 'C';
	char op;


	shmid = shmget(1311017, N*sizeof(struct buffer), 0600|IPC_CREAT);
	shmbuf = (struct buffer *)shmat(shmid, 0, 0);

	semid = semget(13011017, 3, 0600|IPC_CREAT|IPC_EXCL);
	if(semid == -1){
		//(shmbuf)->p_count = 0;
		//(shmbuf)->c_count = 0;
		//위치 잘못넣음 ㅅㅂ
		semid = semget(13011017, 3, 0600);
	}
	else{
		(shmbuf)->p_count = 0;
		(shmbuf)->c_count = 0;
		arg.array = buf;
		semctl(semid, 0, SETALL, arg);
	}
	printf("semid = %d\n", semid);
	printf("semn = %d\n", semctl(semid, 0, GETVAL, 0600));

	printf("check\n");
	//op = argv[1];
	if(strcmp(argv[1],"P")==0){
		producer(semid, shmbuf);
	}
	else if(strcmp(argv[1],"C")==0){
		consumer(semid, shmbuf);
	}
	
	if((shmbuf)->p_count <1 && (shmbuf)->c_count <1){
		semctl(semid, IPC_RMID, 0);
		shmctl(shmid, IPC_RMID, 0);
	}
	
	exit(0);
}

void producer(int semid, struct buffer *buf){
	int in, i;

	printf("im p\n");
	(buf)->p_count++;
	printf("p_count= %d\n", (buf)->p_count);
	while(1){
		sem_op(semid, 2, -1);
		scanf("%d", &in);
		for(i=0;i<N;i++){
			if((buf+i)->flag == 0){
				(buf+i)->data = in;
				(buf+i)->flag = 1;
			
				sem_op(semid, 0, 1);
				sem_op(semid, 2, 1);
				if(in == 0){
					(buf)->p_count --;
					printf("p = %d\n", (buf)->p_count);
					return;
				}
				break;
			}
			else
				continue;
			
		}
	}	
};
void consumer(int semid, struct buffer *buf){
	int out, i;
	
	printf("im c\n");
	(buf)->c_count ++;
	printf("c_count = %d\n", (buf)->c_count);
	while(1){
		for(i=0;i<N;i++){
			sem_op(semid, 1, -1);
			if((buf+i)->flag == 1){
				out = (buf+i)->data;
				(buf+i)->flag = 0;
				printf("read = %d\n", out);
				sem_op(semid, 0, -1);
				if(out == 0){
					(buf)->c_count --;
					printf("c = %d\n",buf->c_count);
					sem_op(semid, 1, 1);
					return;
				}
				break;
			}
		}
	}
};
void sem_op(int semid, int semnum, int sem_op){
	struct sembuf p_buf;
	
	p_buf.sem_num = semnum;
	p_buf.sem_op = sem_op;
	p_buf.sem_flg = 0;
	semop(semid, &p_buf, 1);
};
