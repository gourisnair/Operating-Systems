#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#define pi 3.14
int main()
{
  pid_t pid1, pid2;
  pid1 = fork();
  if(pid1 < 0) {
    printf("Child failed");
  } else {
    if(pid1 == 0) {
      float r;
      scanf("%f", &r);
      printf("Area of circle is %f\n", pi*r*r);
      printf("Circumference of circle if %f\n", 2*pi*r);
    } else {
      pid2 = fork();
      if(pid2 == 0) {
        float a;
        scanf("%f", &a);
        printf("Area of square is %f\n", a*a);
        printf("Perimeter of square is %f\n", 4*a);
      }
    }
  }
}
