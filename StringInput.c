#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
  char *s;
  int shmid = shmget(IPC_PRIVATE, 100, 0666|IPC_CREAT);
  if (fork() == 0) {
    s = (char*)shmat(shmid, (void*)0, 0);
    printf("Enter a string ");
    scanf("%s", s);
  } else {
    wait(NULL);
    s = (char*)shmat(shmid, (void*)0, 0);
    for(int i = 0; i < strlen(s); i++) {
      s[i] = toupper(s[i]);
    }
    printf("Result: %s\n", s);
  }
  exit(0);
}
