#include <stdio.h>

int main() {
    int num_processes, num_resources, i, j, k=0, completed=0, safe_flag=0, exec_count=0;

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    int visited[num_processes];
    int safe_sequence[num_processes];

    int allocation[num_processes][num_resources];
    int max[num_processes][num_resources];
    int available[num_resources];
    int need[num_processes][num_resources];

    printf("Enter the available instances: ");
    for(i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum need of each process:\n");
    for(i = 0; i < num_processes; i++) {
        printf("P%d : ", i);
        for(j = 0; j < num_resources; j++)
            scanf("%d", &max[i][j]);

        visited[i] = 0;
    }

    printf("\nEnter the allocation of resources to each process\n");
    for(i = 0; i < num_processes; i++) {
        printf("P%d : ", i);
        for(j = 0; j < num_resources; j++)
            scanf("%d", &allocation[i][j]);

        visited[i] = 0;
    }

    printf("\nAllocation\tMax\tNeed\n");
    for(i = 0; i < num_processes; i++) {
        for(j = 0; j < num_resources; j++)
            printf("%d ", allocation[i][j]);
        printf("\t\t");
        for(j = 0; j < num_resources; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for(j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while(completed < num_processes) {
        safe_flag = 0;
        for(i = 0; i < num_processes; i++) {
            exec_count = 0;
            for(j = 0; j < num_resources; j++) {
                if(need[i][j] <= available[j])
                    exec_count++;
            }
            if(exec_count == num_resources && visited[i] == 0) {
                for(j = 0; j < num_resources; j++)
                    available[j] += allocation[i][j];
                safe_flag = 1;
                visited[i] = 1;
                safe_sequence[k++] = i;
            }
        }
        if(safe_flag == 0) {
            printf("No safe sequence exists!\n");
            return 1; 
        }
    }

    printf("\nSafe Sequence: ");
    printf("<");
    for(i = 0; i < num_processes; i++)
        printf("P%d ", safe_sequence[i]);
    printf(">\n");

    return 0; 
}
