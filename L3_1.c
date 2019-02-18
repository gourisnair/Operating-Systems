#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#define pi 3.14
int main()
{
  pid_t pid;
  pid = fork();
  if(pid < 0) {
    printf("child failed");
  } else {
    if (pid == 0) {
      float r;
      scanf("%f", &r);
      printf("Area of circle is %f\n", pi*r*r);
      printf("Circumference of circle if %f\n", 2*pi*r);
    } else {
      float a;
      scanf("%f", &a);
      printf("Area of square is %f\n", a*a);
      printf("Perimeter of square is %f\n", 4*a);
    }
  }
}
