#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#define pi 3.14
int main()
{
	float a;
	scanf("%f", &a);
	printf("Area and perimeter of square are %f and %f\n", (a*a), (4*a));
}
