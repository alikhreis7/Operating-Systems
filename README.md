# Operating-Systems

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File: cpr.c

Problem Description: This program contains the code for creation
 of a child process and attach a pipe to it.
	 The child will send messages through the pipe
	 which will then be sent to standard output.

Explanation of the zombie process:

When a process dies in Linux, the process status changes to EXIT_ZOMBIE and it's process that has completed
execution, but still has an entry in the process table. Zombie processes usually occur for child processes,
because the parent prcess must always read the exit status of its child. Once this is done using the wait system
call, this allows the parent process to get information from the dead process. After calling wait(), the zombie
process is completely removed from memory.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
File: sleepingTA.c

Problem Description: 

A university computer science department has a teaching assistant (TA) who helps undergraduate students with their programming 
assignments during regular office hours. The TA’s office is rather small and has room for only one desk with a chair and computer. 
There are three chairs in the hallway outside the office where students can sit and wait if the TA is currently helping another student. 
When there are no students who need help during office hours, the TA sits at the desk and takes a nap. If a student arrives during office hours and finds the TA sleeping, 
the student must awaken the TA to ask for help. If a student arrives and finds the TA currently helping another student, the student sits on one of the chairs in the hallway and waits. 
If no chairs are available, the student will come back at a later time.
Using POSIX threads, mutex locks, and semaphores, implement a solution that coordinates the activities of the TA and the students.

Using Pthreads, begin by creating n students. Each will run as a separate thread. The TA will run as a separate thread as well. 
Student threads will alternate between programming for a period of time and seeking help from the TA. If the TA is available, they will obtain help. 
Otherwise, they will either sit in a chair in the hallway or, if no chairs are available, will resume programming and will seek help at a later time. 
If a student arrives and notices that the TA is sleeping, the student must notify the TA using a semaphore. When the TA finishes helping a student, 
the TA must check to see if there are students waiting for help in the hallway. If so, the TA must help each of these students in turn. 
If no students are present, the TA may return to napping.


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Files: main.c & consumer.c & producer.c

Problem Descriptions: 

 a program that implements the FIFO and LRU page-replacement algorithms presented in this chapter. 
 First, generate a random page-reference string where page numbers range from 0 to 9. Apply the random page-reference string to each algorithm, 
 and record the number of page faults incurred by each algorithm. Implement the replacement algorithms so that the number of page frames can vary from 1 to 7. 
 Assuming that demand paging is used.


The Catalan numbers are an integer sequence Cn that appear in tree-enumeration problems. The first Catalan numbers for n=1,2,3,.... Are 1, 2, 5, 14, 42, 132, ... A formula generating Cn is:
Cn = (2n)!/(n+1)!n!
Design 2 programs (one for the producer and one for the consumer) that communicate with shared memory on Windows or Unix/Linux. The producer process will generate
the Catalan sequence and write it to a shared memory object. The consumer process with then read and output the sequence from shared memory. 
In this instance, the producer process will be passed an integer parameter on the command line specifying the number of Catalan numbers to produce; i.e., 
providing 5 on the command line means the producer process will generate the first 5 Catalan numbers.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
