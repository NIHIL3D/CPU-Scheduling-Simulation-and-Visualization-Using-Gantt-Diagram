#include <iostream>
#include "raylib.h"
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
    string pid;        
    int arrivalTime;    
    int burstTime;      
    int responseTime;
    vector< vector<int> > responseTimes;
    int quantumAccumulated = 0;
    bool isCompleted = false;
    int priority;
    Color color;
};

bool comparearrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

vector<Process> FCFS(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    

    sort(processes.begin(), processes.end(), comparearrivalTime);
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].responseTime = currentTime;
        currentTime += processes[i].burstTime;
    }
    
    return processes;
}

vector<Process> SJF(vector<Process>& processes) {
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
    
    return processes;
}

vector<Process> PS(vector<Process>& processes) {
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
    
    return processes;
}

vector<Process> RoundRobin(vector<Process>& processes, int quantum) {
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
    
    return processes;
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
