// Shortest Remaining Time First (SRTF) CPU Scheduling Algorithm
// Author - Chahat Mittal
// Criteria - Burst Time
// Mode - Preemptive

/*  Input-  No. of processes 
            Arrival Time and Burst Time of each process
    Output- Completion Time (CT), Waiting Time (WT), Turn Around Time (TAT), Response Time (RT) for each process
            Average turn around time
            Average waiting time
*/

#include <stdio.h>
#include <limits.h>

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

// Response time (RT) = (Time when the process got CPU for the first time) - Arrival Time (AT)
double find_response_time(int size, int arrival[], int cpu_first[], int response[]){
    double avg_response = 0;
    for(int i = 0; i < size; i++){
        response[i] = cpu_first[i] - arrival[i];
        avg_response += response[i];
    }
    avg_response = avg_response/size;
    return avg_response;
}

// Driver code
int main(){
    int size,cst;
    int process[size];
    int arrival[size];
    int burst[size];

    printf("Enter context switching time: ");
    scanf("%d",&cst);
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

    int completion[size], tat[size], waiting[size], response[size], remaining[size], cpu_first[size];
    int temp, time = 0; // helping variable during sorting

    // Sorting the arrays based on arrival time
    // If arrival time for two or more process are same, they are sorted on the basis of burst time
    for(int i = 0; i < size; i++){
        for(int j = i+1; j < size; j++){
            if((arrival[j] < arrival[i]) || (arrival[j] == arrival[i] && burst[j] < burst[i])){
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

    int min_burst = INT_MAX;
    int min_burst_index = -1;
    int allot = 0; // Variable for knowing if the process is completed or not

    // Initializing remaining array
    for(int i = 0; i < size; i++){
        remaining[i] = burst[i];
    }

    //  Initializing cpu_first array
    for(int i = 0; i < size; i++){
        cpu_first[i] = -1;
    }

    // If CPU remains idle in the beginning
    if (arrival[0] > time){
        time += arrival[0];
    }

    // Running the first process for 1 unit of time
    remaining[0] -= 1;
    cpu_first[0] = arrival[0];
    if(remaining[0] == 0){
        completion[0] = 1;
        allot++;
    }

    // Increasing time variable by 1 for beginning further processes 
    time += 1;

    while(time > 0){
        min_burst = INT_MAX;
        // Checking all process to identify the one that runs next
        for(int j = 0; j < size; j++){
            if(arrival[j] > time)
                break;
            if(remaining[j] < min_burst && remaining[j] != 0){
                min_burst = remaining[j];
                min_burst_index = j;
            }
        }
        
        // Decreasing the burst time by 1
        remaining[min_burst_index] -= 1;

        // Storing the time as an element of cpu_first array 
        // When a process gets CPU for first time to calculate response time
        if(cpu_first[min_burst_index] == -1){
            cpu_first[min_burst_index] = time;
        }

        // Alloting completion time 
        // When the process completed it's burst time
        if(remaining[min_burst_index] == 0){
            completion[min_burst_index] = time + 1 + cst;
            allot++;
        }

        // Condition to break the loop when all the processes have executed
        if(allot == size){
            break;
        }
        
        // Updating the time by 1 unit 
        time += 1;
    }
    

    double avg_tat = find_turn_around_time(size, arrival, completion, tat);
    double avg_waiting = find_waiting_time(size, burst, tat, waiting);
    double avg_response = find_response_time(size, arrival, cpu_first, response);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(int i = 0; i < size; i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d", process[i], arrival[i], burst[i], completion[i], tat[i], waiting[i], response[i]);
    }

    printf("\nAverage turn around time: %.2f ",avg_tat);
    printf("\nAverage waiting time: %.2f ",avg_waiting);
    printf("\nAverage response time: %.2f ",avg_response);
    printf("\n");
    return 0;
}