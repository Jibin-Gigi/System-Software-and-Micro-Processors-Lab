#include<stdio.h>

struct process{
	int burst_time;
	int waiting_time;
	int turn_around_time;
	int priority;
	int process_id;
	int remaining_time;
};

void calculation(struct process p[],int no_processes, int total_turn_around_time, int total_waiting_time){
	printf("Process	| Waiting Time | Turn Around Time\n");
	for(int i = 0; i<no_processes; i++ ){
		printf("P%d \t\t %d \t\t %d\n",p[i].process_id,p[i].waiting_time,p[i].turn_around_time  );
	}
	printf("Total turn around time = %d\n", total_turn_around_time);
	printf("Total waiting time = %d\n", total_waiting_time);
}
 
 
void gantt_chart(struct process p[], int total_turn_around_time, int total_waiting_time, int no_processes){
	printf("Gantt Chart: \n");
	for(int i =0; i<no_processes ; i++){
		printf(" | ");
		printf("%d", p[i].process_id);
	}
	printf(" | \n0");
	for(int i =0; i<no_processes ; i++){
		printf("   %d", p[i].turn_around_time);
	}
	printf("\n");
	
	printf("Process	| Waiting Time | Turn Around Time\n");
	for(int i = 0; i<no_processes; i++ ){
		printf("P%d \t\t %d \t\t %d\n",p[i].process_id,p[i].waiting_time,p[i].turn_around_time  );
	}
	printf("Total turn around time = %d\n", total_turn_around_time);
	printf("Total waiting time = %d\n", total_waiting_time);
}

void round_robin_gantt_chart(struct process a,struct process p[], int cycle_time[], int total_waiting_time,int no_processes, int completed, int counter){
	int total_turn_around_time = 0;
	printf(" | P%d",a.process_id);
	if(completed == no_processes){
		printf(" |\n");
		for(int i= 0;i<counter;i++){
			printf(" %d   ",cycle_time[i]);
		}
		printf("\n");
		for(int i=0;i<no_processes;i++){
			total_turn_around_time += p[i].turn_around_time;
		}
		calculation( p, no_processes, total_turn_around_time, total_waiting_time);
	}
	
	
	
}



void fcfs(struct process p[], int total_turn_around_time, int total_waiting_time, int no_processes){	
	p[0].waiting_time = 0;
	p[0].turn_around_time = p[0].burst_time;
	
	total_turn_around_time += p[0].waiting_time;
	total_waiting_time += p[0].turn_around_time;
	
	for (int i=1; i<no_processes ; i++){
		p[i].waiting_time = p[i-1].turn_around_time;
        	p[i].turn_around_time = p[i].waiting_time + p[i].burst_time;
		
		total_turn_around_time += p[i].turn_around_time;
		total_waiting_time += p[i].waiting_time ;
	}
	
	gantt_chart(p, total_turn_around_time, total_waiting_time, no_processes);
			
}

void sjf(struct process p[], int total_turn_around_time, int total_waiting_time, int no_processes){
	
	for (int i = 0; i<no_processes -1 ; i++){
		for (int j = i+1; j<no_processes ; j++){
			if (p[i].burst_time > p[j].burst_time){
				struct process temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	
	p[0].waiting_time = 0;
	p[0].turn_around_time = p[0].burst_time;
	
	total_turn_around_time += p[0].waiting_time;
	total_waiting_time += p[0].turn_around_time;
	
	for (int i=1; i<no_processes ; i++){
		p[i].waiting_time = p[i-1].turn_around_time;
        	p[i].turn_around_time = p[i].waiting_time + p[i].burst_time;
		
		total_turn_around_time += p[i].turn_around_time;
		total_waiting_time += p[i].waiting_time ;
	}
	
	gantt_chart(p, total_turn_around_time, total_waiting_time, no_processes);	
}

void priority(struct process p[], int total_turn_around_time, int total_waiting_time, int no_processes){
	for (int i = 0; i<no_processes -1 ; i++){
		for (int j = i+1; j<no_processes ; j++){
			if (p[i].priority > p[j].priority){
				struct process temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
		
	
	p[0].waiting_time = 0;
	p[0].turn_around_time = p[0].burst_time;
	
	total_turn_around_time += p[0].waiting_time;
	total_waiting_time += p[0].turn_around_time;
	
	
	for (int i=1; i<no_processes ; i++){
		p[i].waiting_time = p[i-1].turn_around_time;
        	p[i].turn_around_time = p[i].waiting_time + p[i].burst_time;
		
		total_turn_around_time += p[i].turn_around_time;
		total_waiting_time += p[i].waiting_time ;
	}
	
	gantt_chart(p, total_turn_around_time, total_waiting_time, no_processes);
}

void round_robin(struct process p[], int no_processes){
	int time_quantum,total_waiting_time;
	printf("Enter the time quantum: ");
	scanf("%d", &time_quantum);
	
	for (int i= 0; i<no_processes; i++){
		p[i].remaining_time = p[i].burst_time;
	}
	
	int completed = 0, counter = 1;
	int cycle_time[20];
	
	cycle_time[0] = 0;
	while(completed < no_processes){
		for(int i=0;i<no_processes;i++){
			if( p[i].remaining_time > 0){
				if(p[i].remaining_time > time_quantum){
					p[i].remaining_time -= time_quantum;
					cycle_time[counter] = cycle_time[counter-1] + time_quantum;
					counter++;
					round_robin_gantt_chart(p[i], p,cycle_time,total_waiting_time,no_processes,completed, counter);
					
				}
				else{
					cycle_time[counter] = cycle_time[counter-1] + p[i].remaining_time;
					p[i].turn_around_time = cycle_time[counter];
					p[i].remaining_time = 0;
					p[i].waiting_time = cycle_time[counter] - p[i].burst_time;
					total_waiting_time += p[i].waiting_time;
					completed++;
					counter++;
					round_robin_gantt_chart(p[i], p,cycle_time,total_waiting_time,no_processes,completed, counter);
				}
			}
		}
		
	}
	
	
}



void main(){
	int no_processes;
	printf("Enter the no.of processes: ");
	scanf("%d", &no_processes);
	
	struct process p[no_processes];
	
	printf("Enter the process id, burst time and priority of each process: \n");
	printf("Process   Burst Time   Priority\n");
	
	for(int i=0; i < no_processes; i++){
		printf("P%d\t\t",i);
		p[i].process_id = i;
		scanf("%d", &p[i].burst_time);
		scanf("%d", &p[i].priority);	
	} 
	
	int choice;
	do{
		
		printf("\nEnter your scheduling choice:\n1)FCFS \t2)SJF \t3)Priority \t4)Round Robin \t5)Exit\n" );
		scanf("%d", &choice);
		switch(choice){
			case 1:{
				printf("\n-------------FCFS CPU Scheduling-----------------\n");
				fcfs(p, 0, 0, no_processes);
				printf("--------------------------------------------------\n");
				break;	
			}
			case 2:{
				printf("\n-------------SJF CPU Scheduling-----------------\n");
				sjf(p, 0, 0, no_processes);
				printf("--------------------------------------------------\n");
				break;
			}
			case 3:{
				printf("\n-------------Priority CPU Scheduling-----------------\n");
				priority(p, 0, 0, no_processes);
				printf("--------------------------------------------------\n");
				break;
			}
			case 4:{
				printf("-------------Round Robin CPU Scheduling-----------------\n");
				round_robin(p, no_processes);
				printf("--------------------------------------------------\n");
				break;
			}
		}
	}while(choice != 5);
	

}
