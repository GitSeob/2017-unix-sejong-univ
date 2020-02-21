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

int main(int argc, char **argv){
	int i, type, qid, in, sum;
	key_t key;
	struct qmsg msg;

	printf("check\n");

	type = atoi(argv[1]);

	key = ftok("key", 3);
	qid = msgget(key, 0600|IPC_CREAT);

	//msg.mtype = type;

	for(i=0;i<5;i++){
		scanf("%d", &in);
		printf("check2\n");
		msg.mtype = type;
		msg.num = in;
		msgsnd(qid, &msg, sizeof(int), 0);
		msgrcv(qid, &msg, sizeof(int), type+3, 0);
		printf("I get .... %d\n", msg.num);
	}

	exit(0);
}
