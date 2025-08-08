# ICT-3208 — Operating System Laboratory

This repository contains lab solutions and code implementations for the **Operating System Laboratory (ICT-3208)** course.  
It covers **all major CPU scheduling algorithms** along with **basic Linux commands and operations** for practical OS learning.

---

## 📂 Contents

### 1. CPU Scheduling Algorithms
- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF) — Preemptive & Non-Preemptive**
- **Shortest Remaining Time First (SRTF)**
- **Round Robin (RR)**
- **Priority Scheduling — Preemptive & Non-Preemptive**
- **Multilevel Queue Scheduling**
- **Multilevel Feedback Queue Scheduling**
- **Gantt Chart generation** for each algorithm

Each implementation includes:
- Process structure definition
- Waiting time, turnaround time, and completion time calculations
- Example input/output
- Well-commented source code

---

### 2. Basic Linux Operations
- File management commands (`ls`, `cp`, `mv`, `rm`, `cat`, `touch`, etc.)
- Directory navigation and manipulation (`cd`, `pwd`, `mkdir`, etc.)
- File permissions (`chmod`, `chown`)
- Process management (`ps`, `top`, `kill`)
- Input/Output redirection (`>`, `>>`, `<`, `|`)
- Shell scripting basics

---

## 📦 How to Use

1. **Clone the repository**  
   ```bash
   git clone https://github.com/<your-username>/ICT-3208-Operating-System-Laboratory.git
   cd ICT-3208-Operating-System-Laboratory
2. **Compile and run a CPU scheduling program (example for FCFS in C):**
   ```bash
   gcc fcfs.c -o fcfs
   ./fcfs
3. **Run Linux operation demos
     Most Linux operation examples are provided as shell scripts (.sh) or markdown notes.**
   ```bash
   chmod +x script.sh
   ./script.sh

##📖 Learning Goals
Understand the working principles of different CPU scheduling algorithms.

Practice implementing scheduling logic in C.

Gain hands-on experience with basic Linux operations and shell commands.

Learn process control and time management in operating systems.


##🛠 Requirements
GCC compiler (for C programs)

Bash shell (for Linux commands and scripts)

A Linux environment (or WSL on Windows)



##📜 License
This repository is shared for educational purposes only.

You are free to use and modify the code, but please give credit when redistributing.



##✏️ Author
Himel

Student, Department of ICT

Session: 2020-21

Islamic University, Bangladesh

Course: ICT-3208 — (Operating System Laboratory)
