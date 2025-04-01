#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
};

void findSJF(vector<Process>& processes, int n) {
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Initialize remaining time
    for(int i = 0; i < n; i++) {
        processes[i].rt = processes[i].bt;
    }

    // Process until all processes are completed
    while(complete != n) {
        // Find process with minimum remaining time among the
        // processes that have arrived till current time
        for(int j = 0; j < n; j++) {
            if((processes[j].at <= t) && 
               (processes[j].rt < minm) && 
               (processes[j].rt > 0)) {
                minm = processes[j].rt;
                shortest = j;
                check = true;
            }
        }

        if(check == false) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        processes[shortest].rt--;

        // Update minimum
        minm = processes[shortest].rt;
        if(minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if(processes[shortest].rt == 0) {
            complete++;
            check = false;
            finish_time = t + 1;

            // Calculate completion time
            processes[shortest].ct = finish_time;
            
            // Calculate waiting time
            processes[shortest].wt = processes[shortest].ct - 
                                   processes[shortest].bt - 
                                   processes[shortest].at;

            if(processes[shortest].wt < 0)
                processes[shortest].wt = 0;
        }
        // Increment time
        t++;
    }
}

void calculateTimes(vector<Process>& processes, int n) {
    // Calculate turnaround time
    for(int i = 0; i < n; i++)
        processes[i].tat = processes[i].ct - processes[i].at;

    // Display processes along with all details
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" 
             << processes[i].at << "\t" 
             << processes[i].bt << "\t" 
             << processes[i].ct << "\t" 
             << processes[i].tat << "\t" 
             << processes[i].wt << "\n";
    }

    // Calculate and display average waiting and turnaround time
    float total_wt = 0, total_tat = 0;
    for(int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
    }
    cout << "\nAverage waiting time = " << total_wt/n;
    cout << "\nAverage turnaround time = " << total_tat/n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    
    cout << "Enter Process Id, Arrival Time and Burst Time:\n";
    for(int i = 0; i < n; i++) {
        cout << "Process " << i+1 << ": ";
        cin >> processes[i].pid >> processes[i].at >> processes[i].bt;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), 
         [](Process a, Process b) { return a.at < b.at; });

    findSJF(processes, n);
    calculateTimes(processes, n);

    return 0;
}
