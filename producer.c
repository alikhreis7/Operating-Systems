

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int numCata = -1;
long factorial(long);
long num(long);
void sequence(long *);



void sequence(long *table){
	for (long i = 0; i < numCata; i++){
		table[i] = num(i + 1);} // sort the pointer to the table
}

long num(long numbrss){
	long equal = ((factorial(2 * numbrss)) / (factorial(numbrss) * factorial(1 + numbrss))); // calculates the value of the next Catalan number Cn = (2n)!/(n+1)!n!
	return equal;}

// function for calculating the factorial n of a number
long factorial(long n){
	long result = 1; //initializing the value of the result
	// n factorial
	for (long i = 1; i <= n; ++i){
		result *= i;
	}
	return result;
}

int main(int ac, char *args[]){
	
	while (numCata < 1){
		printf("Enter the number of Catalan you want to have: ");
		scanf("%d", &numCata);
	}
	// array containing a character string for table
	long CataList[numCata];
	sequence(CataList);
	for (int i = 0; i < numCata; i++){
		printf("%li\n", CataList[i]);
	}
	char chain[sizeof(long) * numCata];
	int size = 0;
	for (int i = 0; i < numCata; i++){
		size += sprintf(&chain[size], "%li,", CataList[i]);
	}
	key_t key1 = ftok("shmfile", 65);
	//the identifier of the shared memory associated with the key1
	int shmid = shmget(key1, 1024, 0666 | IPC_CREAT);
	char *str2 = (char *)shmat(shmid, (void *)0, 0);
	strcpy(str2, chain);
	printf("Producer written data to shared memory: %s\n", str2); //Reading and printing the memory list
	shmdt(str2);
	return 0;
}

