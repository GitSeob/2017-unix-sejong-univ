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
        int id;
        int cnt;
        int seq_no;
        char msg[512];
} msg;

msg chatAccess(int);
int receiver(int, int, int);
int sender(int, int);

int main(){
        int     pid, msg_id, id, seq_id, cnt, prompter, c_id, seq_no;
        msg 	msg;        
        
        msg_id = msgget(13011017, 0);
        
        msg = chatAccess(msg_id);
        id = msg.id;
	cnt = msg.cnt;
	seq_no = msg.seq_no;
	
    	pid = fork();
	if(pid == 0)
		receiver(msg_id, id, seq_no);
        
       	sender(msg_id, id);

        kill(pid, SIGINT);
        wait(NULL);

	return 0;
}

msg chatAccess(int msg_id){
	msg msg, msg2;
	msg.mtype = 1; // 1 == ACCESS
	
	msgsnd(msg_id, &msg, sizeof(msg), 0);
	msgrcv(msg_id, &msg, sizeof(msg), 4, 0);

        printf("id = %d\n", msg.id);
	if(msg.cnt == 1) printf("talk_wait...\n");
	else printf("talk_start\n");

	if(msg.cnt == 2){
		msg2.mtype = 2;
		msg2.id = msg.id;
		msgsnd(msg_id, &msg2, sizeof(msg), 0);
		msgrcv(msg_id, &msg2, sizeof(msg), 5+msg.id, 0);

		msg2.mtype = msg.seq_no;
		msg2.id = msg.id;
		msg2.cnt = -1;
		strcpy(msg2.msg, "talk_start");				
			
		msgsnd(msg_id, &msg2, sizeof(msg), 0);		
		msgsnd(msg_id, &msg2, sizeof(msg), 0);		
	}
	return msg;
}

int sender(int msg_id, int id){
	msg msg;
	int seq_no, cnt, i;
	char in[512];
	msg.id = id;
	while(1){
		scanf("%s", in);
		msg.mtype = 2;
		msgsnd(msg_id, &msg, sizeof(msg), 0);
		msgrcv(msg_id, &msg, sizeof(msg), 5+id, 0);

		cnt = msg.cnt;
		if(cnt == 1 && strcmp(in, "talk_quit") != 0){
			printf("talk_wait...\n");
		}
		seq_no = msg.seq_no;

		msg.mtype = seq_no;
		msg.id = id;
		strcpy(msg.msg, in);

		for(i = 0; i < cnt; i++)
			msgsnd(msg_id, &msg, sizeof(msg), 0);
		
		if(strcmp(in, "talk_quit") == 0){
			msg.mtype = 3;
			msgsnd(msg_id, &msg, sizeof(msg), 0);
			return;
		}
	}
		
	
	return 0;
}

int receiver(int msg_id, int id, int seq_no){
	msg msg;
	while(1){
		msgrcv(msg_id, &msg, sizeof(msg), seq_no, 0);
		seq_no++;
		if(msg.id == id) continue;
		else{
			if(msg.cnt == -1) printf("%s\n", msg.msg);
			else printf("%d : %s\n", msg.id, msg.msg);		
		}
	}
	return 0;
}
