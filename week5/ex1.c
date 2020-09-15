#include <stdio.h>
#include <pthread.h>

pthread_mutex_t my_lock;

void* print(void* tid)
{
  pthread_t id = *((pthread_t*)tid);

  pthread_mutex_lock(&my_lock);
  printf("Thread created\n");
  printf("Hi from the thread %lu\n", id);
  printf("Thread exited\n\n");
  pthread_mutex_unlock(&my_lock);


  pthread_exit(NULL);
}

int main()
{
  pthread_t tid[3]; // array of threads' ids

  for (int i = 0; i < 3; i++) {
    pthread_create(tid + i, NULL, &print, (void*)(tid + i));
  }

  pthread_exit(NULL);
}
