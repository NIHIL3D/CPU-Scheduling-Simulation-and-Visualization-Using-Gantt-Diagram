#include <iostream>
#include<vector>
#include<algorithm>
#include<limits>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<conio.h>

using namespace std;


struct Process {
    int pid;        
    int arrivalTime;    
    int burstTime;      
    int responseTime;
    vector< tuple<int, int> > responseTimes;
    int quantumAccumulated;
    bool isCompleted = false;
    int priority;
    int color;
};

bool comparearrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

void FCFS(vector<Process>& processes) {
    int numOfProcesses = processes.size();
    int currentTime = 0;

    sort(processes.begin(), processes.end(), comparearrivalTime);
    for (int i = 0; i < numOfProcesses; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].responseTime = currentTime;
        currentTime += processes[i].burstTime;
    }
    for (int i = 0; i < numOfProcesses; i++){
        cout << 'P' << processes[i].pid << " |" << string(processes[i].responseTime, ' ') << "\033[0;3" << processes[i].color << "m";
        for(int j = 0; j < processes[i].burstTime; j++){
            cout << (char)219u;
        }
        cout << "\033[0m " << endl;
    }
}

void SJF(vector<Process>& processes) {
    int numOfProcesses = processes.size();
    int currentTime = 0;

    sort(processes.begin(), processes.end(), comparearrivalTime);

    while(true){
    	int currentShortestJobIndex = -1;
    	int currentShortestJobRemainingTime = numeric_limits<int>::max();
    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++){
    		if(!processes[i].isCompleted){
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime){
                    if(processes[i].burstTime < currentShortestJobRemainingTime){
                        currentShortestJobRemainingTime = processes[i].burstTime;
                        currentShortestJobIndex = i;
    			    }
                }
    		}
    	}

    	if(isAllCompleted){
    		break;
    	}
		processes[currentShortestJobIndex].responseTime = currentTime;
        currentTime += processes[currentShortestJobIndex].burstTime;
    	processes[currentShortestJobIndex].isCompleted = true;

    }
    for (int i = 0; i < numOfProcesses; i++){
        cout << 'P' << processes[i].pid << " |" << string(processes[i].responseTime, ' ') << "\033[0;3" << processes[i].color << "m";
        for(int j = 0; j < processes[i].burstTime; j++){
            cout << (char)219u;
        }
        cout << "\033[0m " << endl;
    }
}

void PS(vector<Process>& processes) {
    int numOfProcesses = processes.size();
    int currentTime = 0;

    sort(processes.begin(), processes.end(), comparearrivalTime);
    while(true){
    	int currentMostImportentJobIndex = -1;
    	int currentMostImportentJobPriority = numeric_limits<int>::max();
    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++){
    		if(!processes[i].isCompleted){
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime){
                    if(processes[i].priority < currentMostImportentJobPriority){
                        currentMostImportentJobPriority = processes[i].priority;
                        currentMostImportentJobIndex = i;
    			    }
                }
    		}
    	}
    	if(isAllCompleted){
    		break;
    	}

		processes[currentMostImportentJobIndex].responseTime = currentTime;
        currentTime += processes[currentMostImportentJobIndex].burstTime;
    	processes[currentMostImportentJobIndex].isCompleted = true;

    }
    for (int i = 0; i < numOfProcesses; i++){
        cout << 'P' << processes[i].pid << " |" << string(processes[i].responseTime, ' ') << "\033[0;3" << processes[i].color << "m";
        for(int j = 0; j < processes[i].burstTime; j++){
            cout << (char)219u;
        }
        cout << "\033[0m " << endl;
    }
}

void RoundRobin(vector<Process>& processes, int quantum) {
    int numOfProcesses = processes.size();
    int currentTime = 0;

    sort(processes.begin(), processes.end(), comparearrivalTime);
    while(true){
    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++){
    		if(!processes[i].isCompleted){
    			isAllCompleted = false;
                if(processes[i].quantumAccumulated <= processes[i].burstTime){
                    if (processes[i].burstTime - processes[i].quantumAccumulated >= quantum){
                        processes[i].responseTimes.push_back({currentTime,quantum});
                        currentTime += quantum;
                        processes[i].quantumAccumulated += quantum;
                    }
                    else {
                        processes[i].responseTimes.push_back({currentTime,processes[i].burstTime - processes[i].quantumAccumulated});
                        currentTime += quantum;
                        processes[i].isCompleted = true;
                    }
                }
    		}
    	}

    	if(isAllCompleted){
    		break;
    	}
    }
    for (int i = 0; i < numOfProcesses; i++){
        cout << 'P' << processes[i].pid << " |" ;
        for (int j = 0; j < processes[i].responseTimes.size() ; j++){
            if (j==0){
                cout << "\033[0;3" << processes[i].color << "m";
                cout << string(get<0>(processes[i].responseTimes[j]), ' ');
                for(int t = 0; t < get<1>(processes[i].responseTimes[j]); t++){
                    cout << (char)219u;
                }
            }
            else {
                cout << "\033[0;3" << processes[i].color << "m";
                cout << string(get<0>(processes[i].responseTimes[j])-(get<0>(processes[i].responseTimes[j-1])+get<1>(processes[i].responseTimes[j-1])), ' ');
                for(int t = 0; t < get<1>(processes[i].responseTimes[j]); t++){
                    cout << (char)219u;
                }
            }
            
        }
        cout << "\033[0m " << endl;
    }
}

vector<string> split(string str){
    string s;
    stringstream ss(str);
    vector<string> vs;
    while (getline(ss, s, ' ')) {
        vs.push_back(s);
    }
    return vs;
}
void repeatstr(int t, char c){
    for (int i = 0; i<t; i++){
        cout << c;
    }
}