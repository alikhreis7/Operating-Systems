// To use Posix thread, mutex locks and semaphores
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h> // To use sem_post, sem_t, sem_init, sem_wait

#define WaitingChair 3 
void TAgoal(void *arg); //  TA goal
void studentgoal(void *arg); // Student goal
time_t time1;
sem_t ta;
sem_t student;
sem_t wait1;

int chair = WaitingChair;

int main(int argc,char *argv[]){
    int state1=0; // initializing to zero
    pthread_t thread1;
    pthread_t thread2;
    time1=time(NULL)+10;
    // initialization time
    sem_init(&wait1,0,1);
    // initialization student
    sem_init(&student,0,0);
    // initialization TA
    sem_init(&ta,0,1);

    state1=pthread_create(&thread2,NULL,(void *)studentgoal,NULL); // creation of the first student thread
    if(state1!=0)
        printf("Error to create student thread! \n");
    state1=pthread_create(&thread1,NULL,(void *)TAgoal,NULL); // creation of the seond TA thread
    
    if(state1!=0)
        printf("Error to create TA thread! \n");
    pthread_join(thread2,NULL); 
    //Waiting for thread to finish
    pthread_join(thread1,NULL); 
    //Waiting for thread to finish
    exit(0);
    //terminates the program
}

void TAgoal(void *arg){
    while(time(NULL) < time1 || chair < WaitingChair){
        sem_wait(&student);
        sem_wait(&wait1);
        chair= chair+1;
        printf("Number of chairs available waiting for the TA:%d\n",chair);
        sem_post(&wait1);
        sem_post(&ta);
        sleep(3);
        printf("Tutoring assistance is complete\n");
        if(chair == WaitingChair){
            printf("The TA falls asleep\n");
        }
    }
}

void studentgoal(void *arg){
    while(time(NULL) < time1){
        sem_wait(&wait1);
        if(chair >0){
            chair = chair -1;
            printf("A new student arrives in the waiting room, the number of chairs available:%d\n",chair);
            sem_post(&wait1);
            sem_post(&student);
            sem_wait(&ta);
        }else{
            sem_post(&wait1);
            printf("No chair Avaialble! so the student leaves and can come later! \n");
        }
        sleep(1); // sleep 1
    }
}