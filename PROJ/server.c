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
        int c_id;
        int c_cnt;
        int seq_no;
        char msg[512];
} msg;

int main(){
	msg msg;
	int i, qid,temp, clientCnt=0,id=0,squence=10001;
	int size = sizeof(char)*512 + sizeof(int)*3; 

	qid = msgget(105211,0666 | IPC_CREAT );	
		
	while(1)
	{
		msgrcv( qid, &msg, size, 0, 0); // 일단 받고 mtype을 비교
		//sleep(5);

		if( msg.mtype == 1) // access
		{
			clientCnt++;
			id++;
			msg.c_cnt = clientCnt;
			msg.c_id = id;
			msg.seq_no = squence;
			if( clientCnt >= 2)
			{
				strcpy( msg.msg , "talk_start");	
				if(clientCnt == 2){
					temp = msg.c_id;
					msg.c_id = -1;
					msg.mtype = squence;
					msgsnd(qid, &msg, size, 0);
					msg.c_id = temp;
				}
				
			}
			else
			{
				strcpy( msg.msg , "talk_wait");
			}
			msg.mtype =4;
			msgsnd( qid, &msg, size , 0 );
			//sleep(5);	
		}
	
		else if( msg.mtype == 2) // request_info
		{
			msg.seq_no = squence;
			msg.c_cnt = clientCnt;
			msg.mtype = 5+msg.c_id;
			msgsnd( qid, &msg , size , 0);
			squence++;
			//sleep(5);
		}
		else if( msg.mtype == 3) // quit
		{
			clientCnt--;
			//id = msg.c_id;
			msg.c_cnt = clientCnt;
			
			if(clientCnt == 1){
				strcpy( msg.msg, "talk_wait" );
				//temp = msg.c_id;
				msg.mtype = squence;
				msg.c_id = -1;
				
				msgsnd(qid, &msg, size, 0);
				
				//msg.c_id = temp;
			}
			//sleep(5);
			else if(clientCnt == 0){
				msgctl(qid, IPC_RMID, 0);
				return 0;
			}
		}
	
	}
		
	return 0;
}

