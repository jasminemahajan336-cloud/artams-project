# ARTAMS - Advanced Real Time Attendance Management System

Welcome to the official repository for the ARTAMS project by **Team Astra**. This system is designed to be a secure, efficient, and proxy-proof attendance solution, with its core logic built in C for maximum performance and learning.

## 🎯 Project Goal

Our primary objective is to eliminate proxy attendance by using a multi-layered security approach:
1.  **Dynamic Tokens:** Simulating dynamic QR codes that expire to prevent sharing.
2.  **Location Validation:** Ensuring students are physically present in the classroom.
3.  **Efficient Backend:** Using core Data Structures and Algorithms in C for a high-performance engine.

---

## 💻 Tech Stack

- **Core Logic:** C
- **Middleware:** FastCGI
- **Database:** Firebase (for Milestone 2)
- **Frontend:** HTML, CSS, JavaScript (for Milestone 2)

---

## 📁 File Structure & Workflow

This repository is organized into modules. Here's how they work together:

- **/core**: Contains the heart of our system. All data structures and validation logic reside here.
  - `student_db.c`: Manages all student data using a Hash Table.
  - `token_manager.c`: Generates and validates secure, time-sensitive session tokens.
  - `location_validator.c`: Verifies student-provided GPS coordinates.
  - `attendance_log.c`: Handles the in-memory log of attendance records for the CLI demo.
- **/cli**: The command-line interface for testing and demonstrating our core logic.
  - `main.c`: The entry point for our Milestone 1 demo. It integrates all `core` modules to create a functional CLI application.
- **/fastcgi**: This will house our C-based web server for Milestone 2.
  - `server.c`: Listens for HTTP requests and calls the core logic functions.
- **/index.html**: The user-facing web interface for Milestone 2.

---

## 🚀 Milestone 1: How to Build and Run the CLI

### Step 1: Compile the Project

Navigate to the project's root directory (`artams-project/`) and run the following command to compile all the necessary C files into a single executable named `artams_cli`.

```bash
gcc cli/main.c core/*.c -o artams_cli -lm
```
*(Note: The `-lm` flag is included to link the math library, which will be needed for the Haversine formula in `location_validator.c`)*

### Step 2: Run the CLI Demo

After successful compilation, an executable file `artams_cli` will be created. Follow this two-terminal workflow to run the demo:

1.  **Open Two Terminals:** Place them side-by-side. One will be the **Teacher's Terminal**, and the other will be the **Student's Terminal**.

2.  **Run in Both Terminals:** In both terminals, execute the program:
    ```bash
    ./artams_cli
    ```

3.  **Teacher Actions (Terminal 1):**
    - The CLI will show a menu. Select the "Teacher" role.
    - Choose the option to "Start New Session".
    - The application will generate and display a **secure token** (e.g., `a1b2-c3d4-e5f6`). This simulates the dynamic QR code.

4.  **Student Actions (Terminal 2):**
    - In the other terminal, select the "Student" role.
    - Choose "Mark Attendance".
    - The app will prompt you to enter:
      - Your Student ID.
      - The **token** displayed on the Teacher's screen.
      - Your mock GPS coordinates (e.g., `28.7041,77.1025`).

5.  **View Results:**
    - The Student's terminal will immediately show whether the attendance was marked successfully after validating the token and location.
    - The Teacher's terminal can now select "View Attendance Log" to see a real-time list of all students who have been successfully marked.

---

## 👨‍👩‍👧‍👦 Team Astra - Milestone 1 Roles

- **Pawan Joshi (Lead):** `token_manager.c` & `cli/main.c` integration.
- **Anushka:** `student_db.c` & CLI menu/input logic.
- **Jasmine:** `attendance_log.c` & session data structures.
- **Aaditya Uniyal:** `location_validator.c` & GPS input flow.
