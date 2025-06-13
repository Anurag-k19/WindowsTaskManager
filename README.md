# 🧠 Windows Mini Task Manager (Console App in C++)

A lightweight console-based Task Manager for Windows built using C++ and Windows APIs.  
This application allows you to **view**, **refresh**, **search**, and **terminate** running processes from the terminal — just like a mini version of Task Manager!

---

## 🔧 Features

- 🔍 View all currently running processes
- 🔁 Refresh the process list dynamically
- 🔎 Search for a process by partial/full name
- ❌ Kill a process by its PID
- 📊 View memory usage in MB

---

## 💻 Tech Stack

- **Language**: C++
- **Platform**: Windows
- **API Used**: Windows API (`tlhelp32.h`, `psapi.h`)
- **IDE**: Visual Studio 2022 

---

## 🚀 Getting Started

### 🛠️ Build Using Visual Studio

1. Open the `.sln` file in Visual Studio
2. Press `Ctrl + Shift + B` to **build**
3. Run the app with `Ctrl + F5` (without debugging)

### 🔧 Build Manually (Command Line)

Open *Developer Command Prompt for VS* and run:

```bash



===== Mini Task Manager =====
1. View Processes
2. Refresh List
3. Kill Process
4. Search Process by Name
5. Exit
Enter choice:
