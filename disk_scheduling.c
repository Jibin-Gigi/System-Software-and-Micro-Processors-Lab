#include<stdio.h>
#include<stdlib.h>

void asc_sort(int array[], int size){
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j < size; j++){
			if(array[i] > array[j]){
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	
}

void desc_sort(int array[], int size){
	for(int i = 0; i < size-1; i++){
		for(int j = i+1; j < size; j++){
			if(array[i] < array[j]){
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	
}

void fcfs_scheduling(int head, int string[], int n){
	printf("-------------------FCFS SCHEDULING---------------------\n");
	printf("Number string: ");
	for(int i = 0; i < n; i++){
		printf("%d ", string[i]);
	}
	printf("\n");
	
	int distance, total_head_movement = 0;
	for(int i = 0; i < n; i++){
		distance = abs(head - string[i]);
		printf("Head moved from %d to %d in %d distance\n", head, string[i], distance);
		total_head_movement += distance;
		head = string[i];
	}
	
	printf("Total head movement = %d\n", total_head_movement);
	printf("Average head movement = %d\n", total_head_movement/n );
}

void scan_scheduling(int head, int string[], int n, int max_range){
	printf("-------------------SCAN SCHEDULING---------------------\n");
	printf("Number string: ");
	for(int i = 0; i < n; i++){
		printf("%d ", string[i]);
	}
	printf("\n");
	
	int distance, total_head_movement = 0;
	int lsize = 0, rsize = 0 ;
	int left_array[n], right_array[n];
	for(int i = 0; i<n ; i++ ){
		if(head > string[i]){
			left_array[lsize] = string[i];
			lsize++;  
		}
		else{
			right_array[rsize] = string[i];
			rsize++;
		}
	}
	
	int choice;
	printf("Choose the side of execution: \n0)Right 1)Left");
	scanf("%d", &choice);
	if (choice == 0){
	asc_sort(right_array, rsize);
	desc_sort(left_array, lsize);
	
	printf("Left array: ");
	for(int i=0; i<lsize ;i++){
		printf("%d ", left_array[i]);
	}
	printf("\n");
	printf("Right array: ");
	for(int i=0; i<rsize ;i++){
		printf("%d ", right_array[i]);
	}
	printf("\n");
	
	int queue[n+1];
	for(int i = 0; i < rsize; i++){
		queue[i] = right_array[i];
	}
	queue[rsize] = max_range;
	for(int i = 0; i < lsize ; i++){
		queue[rsize + i + 1] = left_array[i];
	}
	
	for(int i = 0; i < n+1; i++){
		distance = abs(head - queue[i]);
		printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
		total_head_movement += distance;
		head = queue[i];
	}
	
	printf("Total head movement = %d\n", total_head_movement);
	printf("Average head movement = %d\n", total_head_movement/n );
	}
	
	
	
	else{
		asc_sort(right_array, rsize);
	desc_sort(left_array, lsize);
	
	printf("Left array: ");
	for(int i=0; i<lsize ;i++){
		printf("%d ", left_array[i]);
	}
	printf("\n");
	printf("Right array: ");
	for(int i=0; i<rsize ;i++){
		printf("%d ", right_array[i]);
	}
	printf("\n");
	
	int queue[n+1];
	for(int i = 0; i < lsize; i++){
		queue[i] = left_array[i];
	}
	queue[lsize] = 0;
	for(int i = 0; i < rsize ; i++){
		queue[lsize + i + 1] = right_array[i];
	}
	
	for(int i = 0; i < n+1; i++){
		distance = abs(head - queue[i]);
		printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
		total_head_movement += distance;
		head = queue[i];
	}
	
	printf("Total head movement = %d\n", total_head_movement);
	printf("Average head movement = %d\n", total_head_movement/n );
	}

}

void c_scan_scheduling(int head, int string[], int n, int max_range){
	printf("-------------------SCAN SCHEDULING---------------------\n");
	printf("Number string: ");
	for(int i = 0; i < n; i++){
		printf("%d ", string[i]);
	}
	printf("\n");
	
	int distance, total_head_movement = 0;
	int lsize = 0, rsize = 0 ;
	int left_array[n], right_array[n];
	for(int i = 0; i<n ; i++ ){
		if(head > string[i]){
			left_array[lsize] = string[i];
			lsize++;  
		}
		else{
			right_array[rsize] = string[i];
			rsize++;
		}
	}
	
	int choice;
	printf("Choose the side of execution: \n0)Right 1)Left");
	scanf("%d", &choice);
	if (choice == 0){
	asc_sort(right_array, rsize);
	asc_sort(left_array, lsize);
	
	printf("Left array: ");
	for(int i=0; i<lsize ;i++){
		printf("%d ", left_array[i]);
	}
	printf("\n");
	printf("Right array: ");
	for(int i=0; i<rsize ;i++){
		printf("%d ", right_array[i]);
	}
	printf("\n");
	
	int queue[n+2];
	for(int i = 0; i < lsize; i++){
		queue[i] = left_array[i];
	}
	queue[lsize] = max_range;
	for(int i = 0; i < rsize ; i++){
		queue[lsize + i + 1] = right_array[i];
	}
	
	for(int i = 0; i < n+2; i++){
		distance = abs(head - queue[i]);
		printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
		total_head_movement += distance;
		head = queue[i];
	}
	
	printf("Total head movement = %d\n", total_head_movement);
	printf("Average head movement = %d\n", total_head_movement/n );
	}
	
	
	
	else{
		asc_sort(right_array, rsize);
	desc_sort(left_array, lsize);
	
	printf("Left array: ");
	for(int i=0; i<lsize ;i++){
		printf("%d ", left_array[i]);
	}
	printf("\n");
	printf("Right array: ");
	for(int i=0; i<rsize ;i++){
		printf("%d ", right_array[i]);
	}
	printf("\n");
	
	int queue[n+1];
	for(int i = 0; i < lsize; i++){
		queue[i] = left_array[i];
	}
	queue[lsize] = 0;
	for(int i = 0; i < rsize ; i++){
		queue[lsize + i + 1] = right_array[i];
	}
	
	for(int i = 0; i < n+1; i++){
		distance = abs(head - queue[i]);
		printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
		total_head_movement += distance;
		head = queue[i];
	}
	
	printf("Total head movement = %d\n", total_head_movement);
	printf("Average head movement = %d\n", total_head_movement/n );
	}
}

void main(){
	int head, no_of_requests, max_range;
	printf("Enter the starting head position: ");
	scanf("%d", &head);
	printf("Enter max range: ");
	scanf("%d", &max_range);
	printf("Enter no.of requests: ");
	scanf("%d", &no_of_requests);
	
	int string[no_of_requests];
	printf("Enter the number string: ");
	for(int i = 0; i < no_of_requests; i++){
		scanf("%d", &string[i]);
	}
	
	int choice;
	do{
		printf("Choose the disk scheduling algorithm: \n1)FCFS \t2)SCAN \t3)C SCAN \t4)exit\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:{
				fcfs_scheduling(head, string, no_of_requests);
				break;
			}
			case 2:{
				scan_scheduling(head, string, no_of_requests, max_range);
				break;
			}
			case 3:{
				c_scan_scheduling(head, string, no_of_requests, max_range);
				break;
			}
		}
	}while(choice != 4);
}
