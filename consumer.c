
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>

int main(int ac, char *args[]){
    key_t key1 = ftok("shmfile", 65); //This is the key with the ID and path
    int shared = shmget(key1, 1024, 0666 | IPC_CREAT); //This is the shared memory identifier
    char * str = (char *)shmat(shared, (void *)0, 0);
    printf("Consumer will read data from shared memory: %s\n", str);
    shmdt(str);
    shmctl(shared, IPC_RMID, NULL); //This will remove shared memory identifier
    return 0;
}