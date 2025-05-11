#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
	key_t key = ftok("shmfile",65);
	if (key == -1) {
	perror("ftok failed");
	return 1;
	}

	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	char *str = (char*) shmat(shmid,(void*)0,0);

	pid_t pid = fork();

if (pid < 0) {
	perror("Fork failed");
	return 1;
	} else if (pid == 0) {
	
	printf("Child writing to shared memory...\n");
	sprintf(str, "Hello from child process!!");
	} else {

	wait (NULL);
	printf("Parent reading from shared memory: %s\n", str);
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);
	}

	return 0;
}
