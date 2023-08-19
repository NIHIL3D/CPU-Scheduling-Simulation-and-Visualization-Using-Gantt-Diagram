#include<iostream>
#include<vector>
#include<algorithm>
#include<windows.h> 
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<conio.h>
#include "SchedulingAlgo.hpp"

using namespace std;

int main() {
    Process process;
    vector<Process> processes;
    int choice;
    int timeQuantum;
    string myline;
    ifstream myfile;
    string fichier ;

    cout << "Insert the address of your file : ";
    cin >> fichier;
    
    myfile.open(fichier);

    if (myfile.is_open()){
        getline(myfile, myline);
        int c = 1, k;
        while (getline(myfile, myline)){
            if (!(myline == "" || myline[0] == '#'))
            {
                vector<string> line = split(myline);
                process.pid = stoi(line[0]);
                process.arrivalTime = stoi(line[1]);
                process.burstTime = stoi(line[2]);
                if (c == 6*k) {
                    process.color = 6;
                    c++;
                }
                else {
                    process.color = c % 6;
                    c++;
                }
                if (line.size()==4){
                    process.priority = stoi(line[3]);
                };
                processes.push_back(process);
            }
        }
    }
    
    cout << "\t\t\t" ; repeatstr(51, '='); cout << endl; 
    cout << "\t\t\t" ; repeatstr(10, '='); cout << "\033[0;31m" << "CPU Scheduling Algorithms" << "\033[0m "; repeatstr(15, '='); cout<< endl; 
    cout << "\t\t\t" ; repeatstr(51, '='); cout << endl; 
    cout << "\t\t\t" ; repeatstr(10, '-'); cout << "\033[0;32m" << "1. First-Come, First-Served (FCFS)" << "\033[0m "; repeatstr(6, '-'); cout << endl; 
    cout << "\t\t\t" ; repeatstr(10, '-'); cout << "\033[0;32m" << "2. Shortest Job First (SJF)" << "\033[0m "; repeatstr(13, '-'); cout << endl; 
    cout << "\t\t\t" ; repeatstr(10, '-'); cout << "\033[0;32m" << "3. Round Robin (RR)" << "\033[0m "; repeatstr(21, '-'); cout << endl; 
    cout << "\t\t\t" ; repeatstr(10, '-'); cout << "\033[0;32m" << "4. Priority Scheduling (PS)" << "\033[0m "; repeatstr(13, '-'); cout << endl;
    cout << "\t\t\t" ; repeatstr(10, '-'); cout << "\033[0;33m" << "Enter your choice (1-4): "<< "\033[0m ";

    cin >> choice;

    switch (choice) {
        case 1:
            // FCFS
            
            FCFS(processes);
            break;
        case 2:
            // SJF
            
            SJF(processes);
            break;
        case 3:
            // Round Robin
            
            cout << "Enter time quantum: ";
            cin >> timeQuantum;
            RoundRobin(processes, timeQuantum);
            break;
            case 4:
            // PS
            
            PS(processes);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
    getch();
    
    

    return 0;
}
