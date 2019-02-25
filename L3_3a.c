#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#define pi 3.14
int main()
{
	float r;
	scanf("%f", &r);
	printf("Area and perimeter of circle is %f and %f\n", (pi*r*r), (2*pi*r) );
}
