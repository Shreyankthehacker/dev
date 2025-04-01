#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid, arrival, burst, priority, remaining, completion, turnaround, waiting;
};

bool arrivalCompare(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool priorityCompare(const Process *a, const Process *b) {
    return a->priority < b->priority;
}

void calculateTimes(std::vector<Process> &processes) {
    int time = 0, completed = 0, n = processes.size();

    while (completed != n) {
        std::vector<Process*> readyQueue;

        for (auto &proc : processes) {
            if (proc.arrival <= time && proc.remaining > 0) {
                readyQueue.push_back(&proc);
            }
        }

        if (!readyQueue.empty()) {
            std::sort(readyQueue.begin(), readyQueue.end(), priorityCompare);
            Process *current = readyQueue.front();
            current->remaining--;
            time++;

            if (current->remaining == 0) {
                completed++;
                current->completion = time;
                current->turnaround = current->completion - current->arrival;
                current->waiting = current->turnaround - current->burst;
            }
        } else {
            time++;
        }
    }
}

void displayProcesses(const std::vector<Process> &processes) {
    std::cout << "PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &proc : processes) {
        std::cout << proc.pid << "\t" << proc.arrival << "\t" << proc.burst << "\t" << proc.priority
                  << "\t\t" << proc.completion << "\t\t" << proc.turnaround << "\t\t" << proc.waiting << "\n";
    }
}

int main() {
    int n;
    std::cout << "Enter number of processes: ";
    std::cin >> n;
    
    std::vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        std::cout << "Enter Arrival Time, Burst Time, and Priority for Process " << i + 1 << ": ";
        std::cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    std::sort(processes.begin(), processes.end(), arrivalCompare);
    calculateTimes(processes);
    displayProcesses(processes);

    return 0;
}
