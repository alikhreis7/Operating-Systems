
#include<stdio.h>
#include<stdlib.h>
#include<time.h> 


void function(int a[], int numofframe);

void function(int a[], int numofframe){
     int indexofval;
     for(indexofval=0;indexofval<numofframe;indexofval++){
          printf("%d ", a[indexofval]);
     }printf("\n");
}
int main(){

     int refpage[11]; // generating a random list of 11 digits
     srand(time(NULL));
     int val;
     for(val=0;val<11;val++){
          refpage[val]=rand()%10; // generating random numbers between 0 and 9
     }
     printf("Page reference string is: \n"); //user input
     function(refpage, 11);
     int frameofpage;
     printf("Enter a page frame from 1 to 7: "); // user input
     scanf("%d", &frameofpage);
     printf("\n");
     if (frameofpage >7){
     printf("Enter a page frame from 1 to 7: "); // user input
     scanf("%d", &frameofpage);
     }

     int frame[frameofpage];
     for(val=0;val<frameofpage;val++){
          frame[val] = -1;
     }
     // FIFO algorithm
     int tour = 0; 
     int faultf = 0;
     int orderf = 0;
     while(tour<11){
          for(val=0; val<frameofpage;val++){
               if(refpage[tour]==frame[val]){
                    break;
               }
               if(val==(frameofpage -1)){
                    faultf++;
                    frame[orderf]=refpage[tour];
                    orderf++;
               }    
          }
          function(frame, frameofpage);
          tour++;
          if(orderf==frameofpage){
               orderf=0;
          }
     }
     printf("\nFIFO page fault = %d\n\n", faultf);


     // LRU algorithm
     int LRU[frameofpage];
     for(val=0;val<frameofpage;val++){
          LRU[val] = -1;
     }
     int x;
     int lfault = 0;
     int ltour = 0;  
     int location = 0; 
     while(ltour<11){
          for(val=0;val<frameofpage;val++){
               if(refpage[ltour]==LRU[val]){
                    location--;
                    for(x=val;x<location;x++){
                         LRU[x]= LRU[x+1];
                    }
                    LRU[location]=refpage[ltour];
                    location++;
                    break;
               }
               if(val==(frameofpage-1)){
                    lfault++;
                    if(location!=frameofpage){
                         LRU[location]=refpage[ltour];
                         location++;
                    }
                    else{
                         for(x=0;x<(frameofpage-1);x++){
                              LRU[x]=LRU[x+1];
                         }
                         LRU[frameofpage-1]=refpage[ltour];
                    }
               }
          }
          function(LRU, frameofpage);
          ltour++;
     }
     printf("\nLRU page fault = %d\n", lfault);
     return 0;  
}
