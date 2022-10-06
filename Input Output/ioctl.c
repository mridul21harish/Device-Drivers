#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>

#define WR_VALUE _IOW('a', 'a', int32_t*)
#define RD_VALUE _IOR('a', 'b', int32_t*)

int main()
{
	int fD;
	int32_t value; int32_t number;
	printf("Opening The Driver\n");
	fD=open("/dev/random", O_RDWR);
	
	if(fD < 0)
	{
		printf("Unable to open the device file\n");
		return 0;
	}
	
	printf("Enter value to send\n");
	scanf("%d", &number);
	
	printf("Writing the value to the driver\n");
	ioctl(fD, WR_VALUE, (int32_t*) &number);
	
	printf("Reading the value from the driver\n");
	ioctl(fD, RD_VALUE, (int32_t*) &value);
	
	printf("The value is %d\n", value);
	
	printf("Closing the driver\n");
	close(fD);
	return 0;
}
