# ARTAMS - CLI Implementation (Milestone 1)

This repository contains the core logic for the ARTAMS project, implemented as a standalone Command-Line Interface (CLI). This serves as our proof-of-concept for all backend functionality.

## 🏗 Project Structure

- **/core**: Contains all core logic modules, separated into `.c` and `.h` files.
- **/cli**: The user-facing CLI entry point (`main.c`).
- **/data**: Flat-file database for the CLI demo.
  - `students.txt`: Pre-populated list of students.
  - `sessions.txt`: Stores the active session token and its expiry.
  - `attendance_log.txt`: A log of all successful attendance markings.
- **Makefile**: Automates the compilation process.

---

## 🚀 How to Build and Run

### 1. Build the Executable

Navigate to the `artams-cli` root directory and run the `make` command. This will compile all source files and create an executable named `artams_cli`.

```bash
make
```

### 2. Run the Demo

Use the two-terminal approach to simulate the teacher-student interaction:

- **Terminal 1 (Teacher):** `./artams_cli`
- **Terminal 2 (Student):** `./artams_cli`

**Teacher Workflow:**
1.  Select Teacher Mode.
2.  Choose "Start Attendance Session".
3.  A token will be generated and saved to `data/sessions.txt`. The token is displayed on screen.

**Student Workflow:**
1.  Select Student Mode.
2.  Enter your Roll Number (must exist in `data/students.txt`).
3.  Enter the token displayed on the teacher's screen.
4.  Enter mock GPS coordinates.
5.  The system validates all inputs and, if successful, appends a record to `data/attendance_log.txt`.

The teacher can then use "View Attendance Log" to see the contents of `attendance_log.txt`.
