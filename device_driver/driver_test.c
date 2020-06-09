#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
	int testdev;
	char buf[30];

	testdev = open("/dev/mycdev",O_RDWR);

	if (testdev == -1){
		printf("open failed\n");
		exit(1);
	}

	if (read(testdev,buf,30) < 30){
		printf("read error.\n");
		exit(1);
	}

	for(int i =0;i<30;i++){
		printf("%c",buf[i]);
	}

	close(testdev);

	return 0;
}