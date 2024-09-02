#include <stdio.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1

void asc_sort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void desc_sort(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void print_arrays(int array[], int size){
	for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void fcfs_scheduling(int head, int string[], int n) {
    printf("-------------------FCFS SCHEDULING---------------------\n");
    printf("Number string: ");
    print_arrays(string, n);

    int distance, total_head_movement = 0;
    for (int i = 0; i < n; i++) {
        distance = abs(head - string[i]);
        printf("Head moved from %d to %d in %d distance\n", head, string[i], distance);
        total_head_movement += distance;
        head = string[i];
    }

    float avg_head_movement = (float)total_head_movement / n;
    printf("Total head movement = %d\n", total_head_movement);
    printf("Average head movement = %.2f\n", avg_head_movement);
    printf("---------------------------------------------------------\n");
}

void scan_scheduling(int head, int string[], int n, int max_range) {
    printf("-------------------SCAN SCHEDULING---------------------\n");
    printf("Number string: ");
    print_arrays(string, n);

    int distance, total_head_movement = 0;
    int lsize = 0, rsize = 0;
    int left_array[n], right_array[n];
    for (int i = 0; i < n; i++) {
        if (head > string[i]) {
            left_array[lsize++] = string[i];
        } else {
            right_array[rsize++] = string[i];
        }
    }

    int choice;
    printf("Choose the side of execution: \n0)Left 1)Right\n");
    scanf("%d", &choice);

    int queue[n + 1];
    int qsize = 0;

    if (choice == RIGHT) {
        asc_sort(right_array, rsize);
        desc_sort(left_array, lsize);

		printf("Right Array: ");
		print_arrays(right_array, rsize);
		printf("Left Array: ");
		print_arrays(left_array, lsize);

        for (int i = 0; i < rsize; i++) queue[qsize++] = right_array[i];
        queue[qsize++] = max_range;
        for (int i = 0; i < lsize; i++) queue[qsize++] = left_array[i];
    } 
	else {
        asc_sort(right_array, rsize);
        desc_sort(left_array, lsize);

		printf("Right Array: ");
		print_arrays(right_array, rsize);
		printf("Left Array: ");
		print_arrays(left_array, lsize);

        for (int i = 0; i < lsize; i++) queue[qsize++] = left_array[i];
        queue[qsize++] = 0;
        for (int i = 0; i < rsize; i++) queue[qsize++] = right_array[i];
    }

    for (int i = 0; i < qsize; i++) {
        distance = abs(head - queue[i]);
        printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
        total_head_movement += distance;
        head = queue[i];
    }

    float avg_head_movement = (float)total_head_movement / n;
    printf("Total head movement = %d\n", total_head_movement);
    printf("Average head movement = %.2f\n", avg_head_movement);
    printf("---------------------------------------------------------\n");
}

void c_scan_scheduling(int head, int string[], int n, int max_range) {
    printf("-------------------C SCAN SCHEDULING---------------------\n");
    printf("Number string: ");
    print_arrays(string, n);

    int distance, total_head_movement = 0;
    int lsize = 0, rsize = 0;
    int left_array[n], right_array[n];
    for (int i = 0; i < n; i++) {
        if (head > string[i]) {
            left_array[lsize++] = string[i];
        } else {
            right_array[rsize++] = string[i];
        }
    }

    int choice;
    printf("Choose the side of execution: \n0)Left 1)Right\n");
    scanf("%d", &choice);

    int queue[n + 2];
    int qsize = 0;

    if (choice == RIGHT) {
        asc_sort(right_array, rsize);
        asc_sort(left_array, lsize);

		printf("Right Array: ");
		print_arrays(right_array, rsize);
		printf("Left Array: ");
		print_arrays(left_array, lsize);

        for (int i = 0; i < rsize; i++) queue[qsize++] = right_array[i];
        queue[qsize++] = max_range;
        queue[qsize++] = 0;
        for (int i = 0; i < lsize; i++) queue[qsize++] = left_array[i];
    } 
	
	else {
        desc_sort(right_array, rsize);
        desc_sort(left_array, lsize);

		printf("Right Array: ");
		print_arrays(right_array, rsize);
		printf("Left Array: ");
		print_arrays(left_array, lsize);

        for (int i = 0; i < lsize; i++) queue[qsize++] = left_array[i];
        queue[qsize++] = 0;
        queue[qsize++] = max_range;
        for (int i = 0; i < rsize; i++) queue[qsize++] = right_array[i];
    }

    for (int i = 0; i < qsize; i++) {
        distance = abs(head - queue[i]);
        printf("Head moved from %d to %d in %d distance\n", head, queue[i], distance);
        total_head_movement += distance;
        head = queue[i];
    }

    float avg_head_movement = (float)total_head_movement / n;
    printf("Total head movement = %d\n", total_head_movement);
    printf("Average head movement = %.2f\n", avg_head_movement);
    printf("---------------------------------------------------------\n");
}

int main() {
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
    do {
        printf("\nChoose the disk scheduling algorithm: \n1)FCFS    2)SCAN    3)C SCAN    4)Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fcfs_scheduling(head, string, no_of_requests);
                break;
            case 2:
                scan_scheduling(head, string, no_of_requests, max_range);
                break;
            case 3:
                c_scan_scheduling(head, string, no_of_requests, max_range);
                break;
            case 4:
				printf("Program exited");
                break;
            default:
                printf("Invalid choice, please choose again.\n");
        }
    } while (choice != 4);

}
