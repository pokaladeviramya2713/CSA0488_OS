#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
};

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        processes[i].processID = i + 1;
        processes[i].arrivalTime = 0;  
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }
    int currentTime = 0;
    for (int i = 0; i < numProcesses; i++) {
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
    }
    printf("\nProcess Schedule (FCFS):\n");
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime);
    }
    float totalWaitTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < numProcesses; i++) {
        totalWaitTime += processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
        totalTurnaroundTime += processes[i].completionTime - processes[i].arrivalTime;
    }
    float avgWaitTime = totalWaitTime / numProcesses;
    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
