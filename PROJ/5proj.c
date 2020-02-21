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
		
struct databuf
{
	long mtype;
	int id;
	int cl_no;
	int seq_no;
	char data[128];
};

void sender(int, struct databuf, int, int);
void rcver(int, struct databuf, int);

int my_id = 1;
int seqn = 2;
int clno = 1;

int main(){
	int qid, i, pid;
	int size = 3*sizeof(int)+sizeof(char)*128;
	char in[128];
	struct databuf msg;
	
	qid = msgget(13011017, 0600|IPC_CREAT|IPC_EXCL);
	if(qid == -1){
		qid = msgget(13011017, 0600);
		msgrcv(qid, &msg, size, 1, 0);
		my_id = msg.id;
		seqn = msg.seq_no;
		clno = msg.cl_no +1;
		msg.id = my_id +1;
		msg.cl_no = clno;
		msg.mtype = 1;
		msgsnd(qid, &msg, size, 0);
	}
	else{
		msg.cl_no = 1;
		msg.seq_no = 2;
		msg.id = 2;
		msg.mtype = 1;
		msgsnd(qid, &msg, size, 0);
	}

	printf("connect .. my id is %d\n", my_id);
	printf("sequence = %d / client num = %d\n", seqn, clno);

	if(pid = fork()==0) rcver(qid, msg, size);

	else sender(qid, msg, size, pid);

	exit(0);
}

void sender(int qid, struct databuf msg, int size, int pid){
	int i;
	char in[512];

	while(1){
		scanf("%s", in);
		msgrcv(qid, &msg, size, 1, 0);
		clno = msg.cl_no;
		seqn = msg.seq_no;
		if(strcmp(in, "quit") == 0){
			msg.cl_no = clno-1;
			if(msg.cl_no == 0){
				printf("REMOVE QUEUE..\n");
				msgctl(qid, IPC_RMID, 0);
			}
			else{
				msg.seq_no  = seqn +1;
				msg.mtype = 1;
				msgsnd(qid, &msg, size, 0);
				printf("client number = %d and %d\n", clno, msg.cl_no);
				msg.id = my_id;
				msg.mtype = seqn;
				strcpy(msg.data, in);
				for(i=0;i<clno;i++){
					msgsnd(qid, &msg, size, 0);
				}
			}
			kill(pid, SIGINT);
			exit(0);
		}
		else{
			msg.seq_no = seqn +1;
			msg.mtype = 1;
			msgsnd(qid, &msg, size, 0);
			msg.id = my_id;
			msg.mtype = seqn;
			strcpy(msg.data, in);
			for(i=0;i<clno;i++){
				msgsnd(qid, &msg, size, 0);
			}
		}
	}
}

void rcver(int qid, struct databuf msg, int size){
	// static struct sigaction act;
	// act.sa_handler = exit(0);
	// sigaction(SIGINT, &act, NULL);

	while(1){
		msgrcv(qid, &msg, size, seqn, 0);
		if(my_id != msg.id){
			printf("%d : %s\n", msg.id, msg.data);
		}
		seqn++;
	}
}