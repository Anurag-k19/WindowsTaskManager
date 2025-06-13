#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ProcessInfo {
    string name ="";
    DWORD pid =0;
    SIZE_T memoryMB =0;
};

void RefreshProcessList(vector<ProcessInfo>& processes) {
    processes.clear();

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (snapshot == INVALID_HANDLE_VALUE) {
        cerr << "Failed to take process snapshot." << endl;
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pe)) {
        do {
            ProcessInfo p;
            p.name = pe.szExeFile;
            p.pid = pe.th32ProcessID;

           
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, p.pid);
            if (hProcess) {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    p.memoryMB = pmc.WorkingSetSize / (1024 * 1024);
                }
                else {
                    p.memoryMB = 0;
                }
                CloseHandle(hProcess);
            }
            else {
                p.memoryMB = 0;
            }

            processes.push_back(p);
        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
}

void DisplayProcesses(const vector<ProcessInfo>& processes) {
    cout << "-------------------------------------------\n";
    cout << "Name\t\tPID\tMemory (MB)\n";
    cout << "-------------------------------------------\n";
    for (const auto& p : processes) {
        cout << p.name << "\t" << p.pid << "\t" << p.memoryMB << endl;
    }
}


void KillProcess(DWORD pid) {
    HANDLE process = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (process == NULL) {
        cerr << "Failed to open process. Error: " << GetLastError() << endl;
        return;
    }

    if (!TerminateProcess(process, 0)) {
        cerr << "Failed to terminate process. Error: " << GetLastError() << endl;
    }
    else {
        cout << "Process " << pid << " terminated successfully." << endl;
    }

    CloseHandle(process);
}
void SearchProcessByName(const vector<ProcessInfo>& processes, const string& target) {
    cout << "-------------------------------------------\n";
    cout << "Matching processes for: " << target << "\n";
    cout << "Name\t\tPID\tMemory (MB)\n";
    cout << "-------------------------------------------\n";

    bool found = false;
    for (const auto& p : processes) {
        if (p.name.find(target) != string::npos) {
            cout << p.name << "\t" << p.pid << "\t" << p.memoryMB << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No process found with name containing \"" << target << "\".\n";
    }
}


int main() {
    vector<ProcessInfo> processes;
    int choice;
    DWORD pid;

    while (true) {
        cout << "\n===== Mini Task Manager =====\n";
        cout << "1. View Processes\n";
        cout << "2. Refresh List\n";
        cout << "3. Kill Process\n";
        cout << "4. Search Process by Name\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            DisplayProcesses(processes);
            break;
        case 2:
            RefreshProcessList(processes);
            cout << "Process list refreshed.\n";
            break;
        case 3:
            cout << "Enter PID to kill: ";
            cin >> pid;
            KillProcess(pid);
            break;
        case 4: {
            string name;
            cout << "Enter process name to search: ";
            cin.ignore(); 
            getline(cin, name);
            SearchProcessByName(processes, name);
            break;
        }
        case 5:
            return 0;

        default:
           cout << "Invalid choice.\n";
        }
    }

    return 0;
}
