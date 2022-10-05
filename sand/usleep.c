#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_sec*1000 + tv.tv_usec/1000); // display in milliseconds
	usleep(1000); // wait 1000 microsec
	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_sec*1000 + tv.tv_usec/1000);
	return 0;
}
