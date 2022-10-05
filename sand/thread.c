#include <stdio.h>
#include <pthread.h>

// count up 10000 times
void *f(void *p) {
	int *cnt;
	int tmp;

	cnt = p;
	for (int i = 0; i < 10000; i++) {
		tmp = *cnt;
		tmp++;
		*cnt = tmp;
	}
	return (NULL);
}

int main() {
	int cnt = 0;
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &f, &cnt);
	pthread_create(&thread2, NULL, &f, &cnt);

	// wait until pthread_create completed.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("cnt : %d\n", cnt);
}
