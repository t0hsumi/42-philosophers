#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

// output the beginning time of threading

void print_time(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_sec*1000 + tv.tv_usec/1000);
	return ;
}

typedef struct s_mut {
	pthread_mutex_t *mutex;
	int *cnt;
} t_mut;

// count up 10000 times
void *f(void *p) {
	t_mut *t;
	int tmp;

	t = p;
	print_time();
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(t->mutex);
		tmp = *t->cnt;
		tmp++;
		*t->cnt = tmp;
		pthread_mutex_unlock(t->mutex);
	}
	return (NULL);
}

int main() {
	int cnt = 0;
	pthread_t thread1;
	pthread_t thread2;

	// initialize mutex objext
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	t_mut t;
	t.mutex = &mutex;
	t.cnt = &cnt;

	print_time();
	pthread_create(&thread1, NULL, &f, &t);
	pthread_create(&thread2, NULL, &f, &t);

	// wait until pthread_create completed.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	print_time();
	pthread_mutex_destroy(&mutex);
	printf("cnt : %d\n", cnt);
}
