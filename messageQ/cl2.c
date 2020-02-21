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

struct mymsg{
	long mtype;
	int mnum;
};

int main(int argc, char **argv){
	int qid, type, i, pid;
	key_t key;
	struct mymsg msg;

	type = atoi(argv[1]);
	pid = getpid();

	msg.mnum = 1;
	msg.mtype = type;

	key = ftok("key2", 3);
	qid = msgget(key, 0600|IPC_CREAT);

	if(type > 1){
		msgrcv(qid, &msg, sizeof(int), type, 0);
	}

	
	for(i=0;i<5;i++){
		sleep(1);
		printf("My pid = %d\n", pid);
	}
	
	if(type<4){
		msg.mtype = type+1;
		msg.mnum = type;
		msgsnd(qid, &msg, sizeof(int), 0);
	}

	return 0;

}
