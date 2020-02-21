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

struct qmsg{
	long mtype;
	int num;
};

int main(){
	printf("Im SERVER\n");
	int i, in, sum, qid;
	key_t key;

	struct qmsg msg;

	key = ftok("key", 3);
	qid = msgget(key, 0600|IPC_CREAT);

	for(i=0;i<15;i++){
		msgrcv(qid, &in, sizeof(int), -3, 0);
		msg.mtype += 3;
		msg.num += 8;
		msgsnd(qid, &msg, sizeof(int), 0);
	}


	exit(0);
}
