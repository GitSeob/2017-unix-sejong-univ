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
// sleep(5) 추가한코드

#define MAX_CLIENT_N 100

typedef struct _msg{
        long mtype;
        int id;
        int cnt;
        int seq_no;
        char msg[512];
} msg;

int main(){
	msg msg;
	int i, qid,temp, clientCnt=0,id=0,squence=MAX_CLIENT_N+1;
	int size = sizeof(msg); 

	qid = msgget(13011017, 0666 | IPC_CREAT );	
		
	while(1)
	{
		msgrcv(qid, &msg, size, -5, 0); // 일단 받고 mtype을 비교
		//sleep(5);

		if( msg.mtype == 1) // access
		{
			clientCnt++;
			id++;
			msg.cnt = clientCnt;
			msg.id = id;
			msg.seq_no = squence;
			msg.mtype =4;
			msgsnd( qid, &msg, size , 0 );
		}
	
		else if( msg.mtype == 2) // request_info
		{
			msg.seq_no = squence;
			msg.cnt = clientCnt;
			msg.mtype = 5+msg.id;
			msgsnd( qid, &msg , size , 0);
			squence++;
			//sleep(5);
		}
		else if( msg.mtype == 3) // quit
		{
			clientCnt--;
			msg.cnt = clientCnt;
			if(clientCnt == 0){
				msgctl(qid, IPC_RMID, 0);
				return 0;
			}
		}
	
	}
		
	return 0;
}

