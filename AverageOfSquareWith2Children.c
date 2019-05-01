//Program where the parent takes inputs unitl met with a special character and squares it.
//Child 1 returns the sum of the squares and child 2 returns its count.
//Parent thereby calculates the average and prints all the results.

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>
#include<sys/types.h>
#include<string.h>
#include<limits.h>
#define r 0
#define w 1
int main()
{
  int fd1[2], fd2[2];
  int sum = 0, count = 0;
  int n[10];

  if(pipe(fd1) == -1) {
    printf("Pipe1 failed");
  }

  if(pipe(fd2) == -1) {
    printf("Pipe2 failed");
  }

  int i = 1;
  printf("Enter the numbers until met with a special character: \n");

  while(1) {
    char temp[10];
    scanf("%s", &temp);
    if(isdigit(temp[0])) {
      int sq = atoi(temp);
      sq *= sq;
      n[i] = sq;
      i++;
    } else {
      n[0] = i;
      break;
    }

  }

  write(fd1[w], n, sizeof(n));
  write(fd2[w], n, sizeof(n));


  if(fork() == 0) {
    read(fd1[r], n, sizeof(n));
    for(int i = 1; i < n[0]; i++) {
      sum += n[i];
    }
    memset(n, 0, sizeof(n));
    n[0] = sum;
    write(fd1[w], n, sizeof(n));
    close(fd1[r]);
  } else {
    wait(NULL);
    read(fd1[r], n, sizeof(n));
    sum = n[0];
    close(fd1[r]);
    if(fork() == 0) {
      read(fd2[r], n, sizeof(n));
      for(int i = 1; i < n[0]; i++) {
        count++;
      }
      memset(n, 0, sizeof(n));
      n[0] = count;
      write(fd2[w], n, sizeof(n));
      close(fd2[w]);
    } else {
      wait(NULL);
      read(fd2[r], n, sizeof(n));
      count = n[0];
      close(fd2[r]);
      printf("\nSum = %d", sum);
      printf("\nCount = %d", count);
      float avg = (float)sum /count;
      printf("\nAvg = %0.2f\n", avg);
    }
  }
}
