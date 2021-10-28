// First Come First Serve (FCFS) Scheduling
// Criteria : Arrival Time
// Mode : Non - preemptive

// Input - Arrival Time and Burst Time of each process
// Output - Completion Time, Turn Around Time, Waiting Time, Response Time for each process


#include <stdio.h>

void find_completion_time(int process[], int size, int arrival[], int burst[], int completion[]){
    completion[0] = burst[0];
    for(int i = 1; i < size; i++){
        if( arrival[i] <= completion[i-1]){
            completion[i] = completion[i-1] + burst[i];
        }
        else
            completion[i] = arrival[i] + burst[i];
        //printf("%d",completion[i]);
    }
}

double find_turn_around_time(int process[], int size, int arrival[], int completion[], int tat[]){
    double avg_tat = 0;
    for(int i = 0; i < size; i++){
        tat[i] = completion[i] - arrival[i];
        avg_tat += tat[i];
        //printf("%d",tat[i]);
    }
    avg_tat = avg_tat/size;
    return avg_tat;
}

double find_waiting_time(int process[], int size, int burst[], int tat[], int waiting[]){
    double avg_waiting = 0;
    for(int i = 0; i < size; i++){
        waiting[i] = tat[i] - burst[i];
        avg_waiting += waiting[i];
        //printf("%d",waiting[i]);
    }
    avg_waiting = avg_waiting/size;
    return avg_waiting;

}

/*void find_response_time(int process[], int size, int arrival[], int completion[], int response[]){
    for(int i = 1; i < size; i++){
        if(completion[i] >= arrival[i]){
            response[i] = completion[i] - arrival[i];
        }
        else
            response[i] = arrival[i];
        //printf("%d",response[i]);
    }
}*/

void print(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver code
int main(){
    /*
    int size = 4;
    int process[size] = {1,2,3,4};
    int arrival[size] = {0,1,5,6};
    int burst[size] = {2,2,3,4};
    */
    int size;
    printf("Enter number of processes: ");
    scanf("%d", &size);
    int process[size];
    for(int i = 0; i < size; i++){
        process[i] = i+1;
    }
    int arrival[size];
    int burst[size];
    printf("Enter arrival time for each process: \n");
    for(int i = 0; i < size; i++){
        scanf("%d", &arrival[i]);
    }
    printf("Enter burst time for each process: \n");
    for(int i = 0; i < size; i++){
        scanf("%d", &burst[i]);
    }

    int completion[size], tat[size], waiting[size], response[size];

    find_completion_time(process, size, arrival, burst, completion);
    double avg_tat = find_turn_around_time(process, size, arrival, completion, tat);
    double avg_waiting = find_waiting_time(process, size, burst, tat, waiting);
    //find_response_time(process, size, arrival, completion, response);
    print(completion,size);
    print(tat,size);
    print(waiting,size);
    //print(response,size);

    printf("Average turn around time: %f ",avg_tat);
    printf("Average waiting time: %f ",avg_waiting);



}