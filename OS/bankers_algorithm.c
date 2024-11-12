#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_processes, num_resources;
    int execution = 0, completion = 0, k = 0, flag = 0;

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    int visited[num_processes], safe_sequence[num_processes];
    int allocation[num_processes][num_resources], max[num_processes][num_resources];
    int available[num_resources];
    int need[num_processes][num_resources];

    printf("Enter the available instances: ");
    for(int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum need of each process:\n");
    for(int i = 0; i < num_processes; i++) {
        printf("P%d : ", i);
        for(int j = 0; j < num_resources; j++)
            scanf("%d", &max[i][j]);
        visited[i] = 0;
    }

    printf("\nEnter the allocation of resources to each process\n");
    for(int i = 0; i < num_processes; i++) {
        printf("P%d : ", i);
        for(int j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);
    }

    for(int i = 0; i < num_processes; i++) {
        for(int j = 0; j < num_resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }

    printf("\n|Allocation\t|Maximum\t|Need\n");
    for(int i = 0; i < num_processes; i++) {
        for(int j = 0; j < num_resources; j++)
            printf("|%d ", allocation[i][j]);
        printf("\t");
        for(int j = 0; j < num_resources; j++)
            printf("|%d ", max[i][j]);
        printf("\t");
        for(int j = 0; j < num_resources; j++)
            printf("|%d ", need[i][j]);
        printf("\n");
    }
    printf("\n");

    while(completion < num_processes) {
        flag = 0;
        for(int i = 0; i < num_processes; i++) {
            execution = 0;
            if(visited[i] == 0) {
                for(int j = 0; j < num_resources; j++) {
                    if(need[i][j] <= available[j])
                        execution++;
                }
                if(execution == num_resources) {
                    for(int j = 0; j < num_resources; j++)
                        available[j] += allocation[i][j];
                    visited[i] = 1;
                    safe_sequence[k++] = i;
                    completion++;
                    flag = 1;
                }
            }
        }
        if(flag == 0) {
            printf("No safe sequence exists!\n");
            exit(0);
        }
    }

    printf("The safe sequence is:\n< ");
    for(int i = 0; i < k; i++)
        printf("P%d ", safe_sequence[i]);
    printf(">\n");

    return 0;
}
