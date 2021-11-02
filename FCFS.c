// First Come First Serve (FCFS) CPU Scheduling algorithm
// Author : Chahat Mittal
// Criteria : Arrival Time
// Mode : Non - preemptive

/*  Input-  No. of processes 
            Arrival Time and Burst Time of each process
    Output- Completion Time (CT), Waiting Time (WT), Turn Around Time (TAT), Response Time (RT) for each process
            Average turn around time
            Average waiting time
*/

#include <stdio.h>

void find_completion_time(int size, int arrival[], int burst[], int completion[]){
    int cst = 1;    // Declaring context switching time in 1 unit
    completion[0] = burst[0] + cst;   // Completion time of first process remains same as burst time
    for(int i = 1; i < size; i++){
        if( arrival[i] <= completion[i-1]){
            completion[i] = completion[i-1] + burst[i] + cst;
        }
        else
            completion[i] = arrival[i] + burst[i] + cst;
    }
}

// Turn around time (TAT) = Completion time (CT) - Arrival time (AT)
double find_turn_around_time(int size, int arrival[], int completion[], int tat[]){
    double avg_tat = 0;
    for(int i = 0; i < size; i++){
        tat[i] = completion[i] - arrival[i];
        avg_tat += tat[i];
    }
    avg_tat = avg_tat/size;
    return avg_tat;
}

// Waiting time (WT) = Turn around Time (TAT) - Burst time (BT)
double find_waiting_time(int size, int burst[], int tat[], int waiting[]){
    double avg_waiting = 0;
    for(int i = 0; i < size; i++){
        waiting[i] = tat[i] - burst[i];
        avg_waiting += waiting[i];
    }
    avg_waiting = avg_waiting/size;
    return avg_waiting;
}

// Response time (RT) = Waiting time (WT)
// For non - preemptive process only
void find_response_time(int size, int waiting[], int response[]){
    for(int i = 0; i < size; i++){
        response[i] = waiting[i];
    }
}

// In general, Response time (RT) = (time at which process gets CPU for the first time) - Arrival time
/*void find_response_time(int size, int arrival[], int completion[], int response[]){
    response[0] = arrival[0];
    for(int i = 1; i < size; i++){
        if(completion[i-1] >= arrival[i]){
            response[i] = completion[i-1] - arrival[i];
        }
        else
            response[i] = 0;
    }
}*/

// Driver code
int main(){
    int size;
    int process[size];
    int arrival[size];
    int burst[size];

    printf("Considering context switching time of 1 unit");
    printf("\nEnter number of processes: ");
    scanf("%d", &size);
    for(int i = 0; i < size; i++){
        process[i] = i+1;
    }

    printf("Enter arrival time for each process: \n");
    for(int i = 0; i < size; i++){
        scanf("%d", &arrival[i]);
    }

    printf("Enter burst time for each process: \n");
    for(int i = 0; i < size; i++){
        scanf("%d", &burst[i]);
    }

    int completion[size], tat[size], waiting[size], response[size];
    int temp; // helping variable during sorting

    // Sorting the arrays based on arrival time
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if(arrival[j] < arrival[i]){
                // swaping elements in arrival array
                temp = arrival[j];
                arrival[j] = arrival[i];
                arrival[i] = temp;
                
                // swaping elements in burst array
                temp = burst[j];
                burst[j] = burst[i];
                burst[i] = temp;

                // swaping elements in process array
                temp = process[j];
                process[j] = process[i];
                process[i] = temp;
            }
        }
    }

    find_completion_time(size, arrival, burst, completion);
    double avg_tat = find_turn_around_time(size, arrival, completion, tat);
    double avg_waiting = find_waiting_time(size, burst, tat, waiting);
    find_response_time(size, waiting, response);
    

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(int i = 0; i < size; i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d", process[i], arrival[i], burst[i], completion[i], tat[i], waiting[i], response[i]);
    }

    printf("\nAverage turn around time: %.2f ",avg_tat);
    printf("\nAverage waiting time: %.2f ",avg_waiting);
    printf("\n");
    return 0;
}