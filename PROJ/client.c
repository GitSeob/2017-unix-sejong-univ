#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX_CLIENT_N 100

typedef struct _msg{
        long mtype;
        int c_id;
        int c_cnt;
        int seq_no;
        char msg[512];
} msg;

int c_id;
int c_cnt;

int chatAccess(int, msg*);
int receiver(int, msg*);
int sender(int, msg*, int);

int main(){
    int     pid, msg_id, mq_key, prompter, c_id, seq_no;
    msg 	msg;        
        
    msg_id = msgget(105211, 0);
        
    chatAccess(msg_id, &msg);
    c_id = msg.c_id;
	
	pid = fork();
	if(pid == 0)
		receiver(msg_id, &msg);
        
       	sender(msg_id, &msg, pid);

        // kill(pid, SIGINT);
        wait(NULL);

	return 0;
}

int chatAccess(int msg_id, msg* msg){
	msg->mtype = 1; // 1 == ACCESS
	
	msgsnd(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 0);
	msgrcv(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 4, 0);
	c_id = msg->c_id;
	c_cnt = msg->c_cnt;
	printf("%s\n", msg->msg);
        printf("id = %d\n", c_id);
	return 0;
}

int sender(int msg_id, msg* msg, int pid){
	int i;
	int seq_no;
	int c_id = msg->c_id;
	seq_no = msg->seq_no;
	while(1){
		scanf("%s", msg->msg);
		msg->c_id = c_id;
		msg->mtype = 2;
		msgsnd(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 0);
		msgrcv(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 5+c_id, 0);
		
		seq_no = msg->seq_no;
		msg->mtype = seq_no;

		msg->c_id = c_id;
		c_cnt = msg->c_cnt;

		for(i = 0; i < c_cnt; i++)
			msgsnd(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 0);
		
		if(strcmp(msg->msg, "talk_quit") == 0){
			kill(pid, SIGINT);
			msg->mtype = 3;
			msgsnd(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, 0);
			return;
		}
	}
		
	
	return 0;
}

int receiver(int msg_id, msg* msg){
	int seq_no = msg->seq_no;
	while(1){
		msgrcv(msg_id, msg, sizeof(char)*512 + sizeof(int)*3, seq_no, 0);

		// if(strcmp(msg->msg, "talk_start") == 0); //|| strcmp(msg->msg, "talk_wait") == 0);
		// else seq_no++;
		seq_no++;
		if(msg->c_id == c_id){
			 continue;
		}
		else{
			if(strcmp(msg->msg, "talk_start")==0 || strcmp(msg->msg, "talk_wait") == 0){
			// if(msg->c_id == -1){
				printf("%s\n", msg->msg);
				seq_no --;
			}else
				printf("%d : %s\n", msg->c_id, msg->msg);
		}
	}
	return 0;
}
