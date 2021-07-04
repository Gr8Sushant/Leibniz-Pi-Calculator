#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<math.h>

//Declaring structutre and double variable
struct count{
	long long start; 		
	long long end;		
};
double num;


//this is the thread function
void *calcPi(void *arg){
	
	double p;
  	struct count * val = (struct count*) arg;
  	
  	//transferring structure value to local variables
	long long start = val -> start;
	long long end = val -> end;
	
	long long i;
	
	for(i=start;i<=end;i++){
		//Using leibniz's formula to calculate estimated pi value
		p=pow(-1,i); 			
		num = num + ((p)/(double)((2*i)+1));
		
	}
	pthread_exit(NULL); //exiting thread
	
}


void main(){ // main method

	int i; 
	long long itr; //no of iteration
	int n; //no of threads

	printf("Enter number of thread to be used:");
	scanf("%d",&n);
	printf("------------------------------------\n");
	
	printf("Enter number of iteration:");
	scanf("%llld",&itr);
	printf("-------------------------------------\n");

	
	

	int slice_List[n]; //initializing array slice_list
	
	//Storing remainder value to rem
	int rem=itr%n;	
	
	//storing quotient value to slice_list
	for(i=0;i<n;i++){
		slice_List[i]=itr/n;
	}
	
	for(i=0;i<rem;i++){
		slice_List[i]=slice_List[i]+1;
	}
	
	//Declaring start and end array
	int start[n];
	int end[n];
	
	
	for(i=0;i<n;i++){ //assigning start and end value
		if(i==0){
			start[i]=0; 
		}
		else{
			start[i]=end[i-1]+1;
		}
		
		end[i] =start[i]+slice_List[i]-1;
	}
	
	
	struct count varStruct[n]; //Initializing structure variable (struct variable)
	int j;
	for(j=0;j<n;j++){
		varStruct[j].start= start[j];
		varStruct[j].end= end[j];
	}

	int k;	
	
	//initializing thread
	pthread_t threads[n]; 
	
	for(k=0;k<n;k++){
		//creating threads
		pthread_create(&threads[k],NULL,calcPi,&varStruct[k]); 
	}
	
	int l;
	
	for(l=0;l<n;l++){
		//joining pthreads
		pthread_join(threads[l],NULL);
	}
		//calculating Pi value
	 	num = num * 4; 
	 	//printing pi value
		printf("The value of Pi is:%lf",num); 
}
