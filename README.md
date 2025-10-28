<div align="center">

# 🎓 ARTAMS
### Advanced Real-Time Attendance Management System

[![C](https://img.shields.io/badge/C-99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/pwnjoshi/artams-project)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)](https://github.com/pwnjoshi/artams-project)

*A lightweight, secure, and efficient command-line attendance management system with GPS validation and time-based token authentication*

[Features](#-features) • [Quick Start](#-quick-start) • [Architecture](#-architecture) • [Usage](#-usage) • [Contributing](#-contributing)

---

</div>

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [System Architecture](#-system-architecture)
- [Installation](#-installation)
- [Quick Start](#-quick-start)
- [User Guide](#-user-guide)
- [Technical Details](#-technical-details)
- [Configuration](#-configuration)
- [Testing](#-testing)
- [Troubleshooting](#-troubleshooting)
- [Roadmap](#-roadmap)
- [Contributing](#-contributing)
- [License](#-license)

## 🌟 Overview

**ARTAMS** is a modern, secure attendance management system designed for educational institutions. Built entirely in C, it provides a robust command-line interface for managing student attendance with advanced features like GPS-based location validation and time-sensitive token authentication.

### Why ARTAMS?

- 🔒 **Secure**: Token-based authentication with automatic expiration
- 📍 **Location-Aware**: GPS validation ensures physical presence
- ⚡ **Fast**: Optimized C implementation with minimal dependencies
- 💾 **Lightweight**: File-based storage, no database required
- 🎯 **Simple**: Intuitive CLI interface for both teachers and students

## ✨ Key Features

### Core Functionality

| Feature | Description |
|---------|-------------|
| 🔐 **Token Authentication** | Simple file-based tokens with 30-second validity |
| 📡 **GPS Validation** | Location-based verification within 100m radius of classroom |
| 👥 **Student Database** | Efficient hash table-based student lookup system |
| 📊 **Attendance Logging** | Chronological linked-list storage with file persistence |
| 🔄 **Auto-Renewal** | Automatic token regeneration for continuous sessions |
| � **Simple Storage** | File-based token storage without heavy data structures |

### Security Features

- ✅ Time-limited session tokens (configurable duration)
- ✅ Geographic boundary validation
- ✅ Student identity verification
- ✅ Secure file-based data persistence
- ✅ Input validation and retry mechanisms

## 🏗 System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    ARTAMS Architecture                       │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  ┌──────────────┐         ┌──────────────┐                  │
│  │   Teacher    │         │   Student    │                  │
│  │  Interface   │         │  Interface   │                  │
│  └──────┬───────┘         └──────┬───────┘                  │
│         │                        │                           │
│         └────────────┬───────────┘                          │
│                      │                                       │
│              ┌───────▼────────┐                             │
│              │   Main Menu    │                             │
│              │  Navigation    │                             │
│              └───────┬────────┘                             │
│                      │                                       │
│         ┌────────────┼────────────┐                         │
│         │            │            │                         │
│    ┌────▼───┐  ┌────▼────┐  ┌────▼────┐                   │
│    │ Token  │  │Location │  │ Student │                    │
│    │Manager │  │Validator│  │Database │                    │
│    └────┬───┘  └────┬────┘  └────┬────┘                   │
│         │           │            │                          │
│         └───────────┼────────────┘                         │
│                     │                                        │
│              ┌──────▼──────┐                                │
│              │    Log      │                                │
│              │  Manager    │                                │
│              └──────┬──────┘                                │
│                     │                                        │
│              ┌──────▼──────┐                                │
│              │ File System │                                │
│              └─────────────┘                                │
└─────────────────────────────────────────────────────────────┘
```

### Project Structure

```
artams-project/
│
├── 📂 cli/
│   └── main.c                    # CLI interface & navigation logic
│
├── 📂 core/
│   ├── student_db.c/.h           # Hash table-based student database
│   ├── token_manager.c/.h        # Token generation & validation
│   ├── log_manager.c/.h          # Attendance logging (linked list)
│   ├── location_validator.c/.h   # GPS coordinate validation
│   └── utils.c/.h                # Utility functions & helpers
│
├── 📂 data/
│   ├── students.txt              # Student records database
│   ├── sessions.txt              # Active session tokens
│   └── attendance_log.txt        # Attendance history
│
├── Makefile                      # Build automation (Unix)
└── README.md                     # This file
```

## 📥 Installation

### Prerequisites

- **C Compiler**: GCC (MinGW on Windows) or Clang
- **C Standard**: C99 or later
- **Math Library**: libm (usually included)

### Windows

```powershell
# Install MinGW-w64 or TDM-GCC
# Clone the repository
git clone https://github.com/pwnjoshi/artams-project.git
cd artams-project

# Option 1: Use batch file (Easiest)
.\run.bat

# Option 2: Build only
.\build.bat

# Option 3: Manual compile
gcc -Wall -Wextra -std=c99 -I core core\*.c cli\*.c -o artams_cli.exe -lm

# Run
.\artams_cli.exe
```

### Linux / macOS

```bash
# Clone the repository
git clone https://github.com/pwnjoshi/artams-project.git
cd artams-project

# Compile using Makefile
make

# Run
./artams_cli
```

## 🚀 Quick Start

### 1. Compile the Project

```bash
gcc -Wall -Wextra -std=c99 -I./core core/*.c cli/*.c -o artams_cli -lm
```

### 2. Run the Application

```bash
./artams_cli
```

### 3. Test with Sample Data

The system comes pre-loaded with sample students:

| Roll No | Name |
|---------|------|
| 101 | Pawan Joshi |
| 102 | Anushka Goel |
| 103 | Jasmine Mahajan |
| 104 | Aaditya Uniyal |

## 📖 User Guide

### 👨‍🏫 Teacher Workflow

```
1. Select Teacher Mode (1)
   │
   ├─→ 2. Start Attendance Session (1)
   │   └─→ Set classroom location (lat, lon)
   │   └─→ Token auto-generates and renews every 30s
   │   └─→ Share token with students
   │   └─→ Press 'q' to stop session
   │
   ├─→ 3. View Attendance Log (2)
   │   └─→ See all attendance records
   │
   └─→ 4. Return to Main Menu (3)
```

**Example Session:**

```
=== ARTAMS - Attendance Management System ===

=== Main Menu ===
Select mode:
    (1) Teacher
    (2) Student
    (3) Exit
> 1

----Teacher Menu----
1. Start Attendance Session
2. View Attendance Log
3. Return to Main Menu
> 1

=== Classroom Location Setup ===
Enter classroom latitude: 28.6139
Enter classroom longitude: 77.2090
Classroom location set to (28.613900, 77.209000) successfully

Press 'q' and Enter to stop the session

[SESSION 1] New token generated: K7M2X9P4
[TOKEN] K7M2X9P4 (expires in 30 seconds) - Press 'q' + Enter to stop
```

### 👨‍🎓 Student Workflow

```
1. Select Student Mode (2)
   │
   ├─→ 2. Enter Roll Number
   │   └─→ System validates student exists
   │
   ├─→ 3. Enter Token (from teacher)
   │   └─→ System validates token & expiry
   │
   └─→ 4. Enter GPS Coordinates
       └─→ System validates location (within 100m)
       └─→ ✅ Attendance marked!
```

**Example Session:**

```
=== Student Attendance Marking ===
Current classroom location: (28.613900, 77.209000)
You must be within 100 meters of this location

Enter Roll No: 101
Student found: Pawan Joshi

Enter Token: K7M2X9P4
Token validated successfully!

Enter Location (latitude longitude): 
Use coordinates near (28.613900, 77.209000) for valid attendance
Enter both values on the same line, separated by space
Latitude Longitude: 28.6140 77.2091

Location validated successfully!
Attendance marked for Pawan Joshi (Roll 101)
Your location: (28.614000, 77.209100)
Returning to main menu...
```

## 🔧 Technical Details

### Data Structures

| Component | Data Structure | Purpose | Time Complexity |
|-----------|---------------|---------|-----------------|
| Student Database | Hash Table | Fast student lookup | O(1) average |
| Attendance Log | Linked List | Chronological ordering | O(n) insertion |
| Token Storage | File-based | Persistence & validation | O(1) read/write |

### Token Management

- **Generation**: Random 8-character alphanumeric strings using srand/rand
- **Character Set**: `A-Z` and `0-9` (36 possible characters)
- **Storage**: Simple file-based storage in `data/sessions.txt`
- **Format**: `<TOKEN> <EXPIRY_UNIX_TIMESTAMP>`
- **Validity Period**: 30 seconds (configurable)
- **Auto-Renewal**: Seamless token regeneration with overwrite
- **Validation**: File-based read and timestamp comparison

### Location Validation

```c
Distance Calculation: Haversine Formula
Radius: 100 meters (0.1 km)
Precision: 6 decimal places (~0.11m accuracy)
Validation: Real-time coordinate checking
Error Feedback: Shows actual distance when validation fails
Input Format: Both coordinates on same line (e.g., "28.6139 77.2090")
```

## ⚙️ Configuration

### Modify Classroom Location

Edit in `cli/main.c`:
```c
setClassroomLocation(28.6139, 77.2090);  // New Delhi coordinates
```

### Adjust Token Validity

Edit in `cli/main.c`:
```c
displayToken(30);  // 30 seconds
```

### Change Location Radius

Edit in `core/location_validator.c`:
```c
#define CLASSROOM_RADIUS_KM 0.1  // 100 meters
```

## 🧪 Testing

### Test Scenarios

#### ✅ Valid Scenarios

```bash
# Valid student
Roll No: 101
Token: (current valid token)
Location: 28.6140 77.2091

# Expected: ✅ Attendance marked successfully
```

#### ❌ Invalid Scenarios

```bash
# Invalid student
Roll No: 999
# Expected: ❌ Student not found

# Expired token
Token: (31+ seconds old)
# Expected: ❌ Invalid or expired token

# Out of range location
Location: 0.0 0.0
# Expected: ❌ Location outside classroom range
```

### Sample Test Coordinates

| Location | Latitude | Longitude | Distance | Valid? |
|----------|----------|-----------|----------|--------|
| Classroom Center | 28.6139 | 77.2090 | 0m | ✅ |
| Nearby (50m) | 28.6143 | 77.2095 | ~50m | ✅ |
| Edge (100m) | 28.6148 | 77.2090 | ~100m | ✅ |
| Far (500m) | 28.6180 | 77.2090 | ~500m | ❌ |

## 🔍 Troubleshooting

<details>
<summary><b>Compilation Errors</b></summary>

```bash
# Error: gcc not found
Solution: Install MinGW (Windows) or build-essential (Linux)

# Error: math.h library not found
Solution: Add -lm flag to compilation command

# Error: header files not found
Solution: Ensure -I./core flag is included
```
</details>

<details>
<summary><b>Runtime Errors</b></summary>

```bash
# Student not found
- Check data/students.txt exists
- Verify roll number is in the file
- Ensure correct file format: "RollNo,Name"

# Token expired
- Generate new token from teacher menu
- Ensure token is entered within 30 seconds
- Token auto-renews during active session

# Location validation failed
- Enter coordinates on SAME LINE separated by space
- Example: 28.6140 77.2091 (not on separate lines)
- Use coordinates near classroom location
- Check GPS precision (6 decimal places recommended)
- System shows actual distance when validation fails
- Verify classroom location is set correctly before student attempts
```
</details>

<details>
<summary><b>Data File Issues</b></summary>

```bash
# Missing data files
Solution: Create data/ directory and required .txt files

# Corrupted attendance log
Solution: Backup and delete attendance_log.txt (auto-regenerates)

# Session token issues
Solution: Delete sessions.txt and regenerate token
```
</details>

## 🗺 Roadmap

### Version 2.0 (Planned)

- [ ] Web-based dashboard interface
- [ ] SQLite database integration
- [ ] Multi-classroom support
- [ ] Attendance analytics & reports
- [ ] Email notifications
- [ ] CSV export functionality

### Version 3.0 (Future)

- [ ] Mobile app (Android/iOS)
- [ ] Real-time GPS tracking
- [ ] QR code authentication
- [ ] Biometric integration
- [ ] Cloud synchronization
- [ ] Admin panel

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. 🍴 Fork the repository
2. 🌿 Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. 💾 Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. 📤 Push to the branch (`git push origin feature/AmazingFeature`)
5. 🎉 Open a Pull Request

### Development Guidelines

- Follow C99 standard
- Maintain consistent code style
- Add comments for complex logic
- Test thoroughly before PR
- Update documentation as needed

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by modern attendance management needs
- Built with performance and security in mind
- Designed for educational institutions

## 📧 Contact

**Pawan Joshi** - [@pwnjoshi](https://github.com/pwnjoshi)

Project Link: [https://github.com/pwnjoshi/artams-project](https://github.com/pwnjoshi/artams-project)

---

<div align="center">

**Made with ❤️ by Pawan, Anushka, Jasmine, Aaditya**

⭐ Star this repo if you find it helpful!

[![GitHub stars](https://img.shields.io/github/stars/pwnjoshi/artams-project?style=social)](https://github.com/pwnjoshi/artams-project/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/pwnjoshi/artams-project?style=social)](https://github.com/pwnjoshi/artams-project/network/members)

</div>

### 🏗 Project Structure

```
artams-project/
├── cli/
│   └── main.c              # Main CLI interface and navigation
├── core/
│   ├── student_db.c/.h     # Student database with hash table
│   ├── token_manager.c/.h  # Simple file-based token management
│   ├── log_manager.c/.h    # Attendance logging system (linked list)
│   ├── location_validator.c/.h # GPS location validation with Haversine
│   └── utils.c/.h          # Utility functions (input, display, etc.)
├── data/
│   ├── students.txt        # Pre-populated student database
│   ├── sessions.txt        # Current active token (auto-generated)
│   └── attendance_log.txt  # Attendance records (auto-saved)
├── Makefile               # Build automation (Linux/Mac)
├── build.bat             # Build script (Windows)
├── run.bat              # Build and run (Windows)
├── clean.bat           # Clean build files (Windows)
└── README.md          # This file
```

## 🚀 How to Build and Run

### Windows (Recommended)

#### Option 1: Using Batch Files (Easiest)
1. **Build and Run**: Double-click `run.bat`
2. **Build Only**: Double-click `build.bat`
3. **Clean Build Files**: Double-click `clean.bat`

#### Option 2: Command Line
```cmd
# Build
gcc -Wall -Wextra -std=c99 -I core core\*.c cli\*.c -o artams_cli.exe -lm

# Run
artams_cli.exe

# Clean (optional)
del *.exe *.o core\*.o cli\*.o
```

### Linux/Mac

1. **Using Make**:
   ```bash
   make
   ./artams_cli
   
   # Clean
   make clean
   ```

2. **Manual Build**:
   ```bash
   gcc -Wall -Wextra -std=c99 -I core core/*.c cli/*.c -o artams_cli -lm
   ./artams_cli
   ```

## 🎯 Features Implemented

### ✅ Core Functionality
- **Student Database**: Hash table-based student lookup system (O(1) average)
- **Token Management**: Simple file-based token generation with expiry validation
- **Location Validation**: GPS-based attendance verification using Haversine formula (100m radius)
- **Attendance Logging**: Linked-list based attendance record keeping with file persistence
- **CLI Navigation**: User-friendly teacher and student interfaces with retry mechanisms

### ✅ Security Features
- Time-limited session tokens (30 seconds default, configurable)
- Location-based attendance verification with distance feedback
- Student identity validation against database
- Secure file-based data storage with auto-save
- Input validation and error handling with retry prompts

## 📱 How to Use

### Teacher Workflow:
1. Run the program and select **Teacher Mode (1)**
2. Choose **"Start Attendance Session (1)"**
3. Enter classroom location (latitude and longitude)
4. A secure token will be generated and auto-renews every 30 seconds
5. Share this token with students for attendance marking
6. Press 'q' and Enter to stop the session
7. Use **"View Attendance Log (2)"** to see all attendance records

### Student Workflow:
1. Run the program and select **Student Mode (2)**
2. Enter your **Roll Number** (must exist in students database)
3. Enter the **token** provided by teacher (within 30 seconds of generation)
4. Enter your **GPS coordinates** (latitude longitude on same line)
   - Example format: `28.6140 77.2091`
   - For testing: Use coordinates near `28.6139 77.2090` (classroom location)
   - Must be within 100 meters of classroom
5. System validates all inputs and marks attendance if successful
6. View detailed distance feedback if location validation fails

## 📊 Sample Usage

### Teacher Session:
```
=== ARTAMS - Attendance Management System ===
Select mode: (1) Teacher  (2) Student  (3) Exit
> 1

----Teacher Menu----
1. Start Attendance Session
2. View Attendance Log
3. Return to Main Menu
> 1

=== Classroom Location Setup ===
Enter classroom latitude: 28.6139
Enter classroom longitude: 77.2090
Classroom location set to (28.613900, 77.209000) successfully

Press 'q' and Enter to stop the session

[SESSION 1] New token generated: A2B9X7K1
[TOKEN] A2B9X7K1 (expires in 30 seconds) - Press 'q' + Enter to stop
```

### Student Session:
```
=== ARTAMS - Attendance Management System ===
Select mode: (1) Teacher  (2) Student  (3) Exit
> 2

=== Student Attendance Marking ===
Current classroom location: (28.613900, 77.209000)
You must be within 100 meters of this location

Enter Roll No: 101
Student found: Pawan Joshi

Enter Token: A2B9X7K1
Token validated successfully!

Enter Location (latitude longitude): 
Use coordinates near (28.613900, 77.209000) for valid attendance
Enter both values on the same line, separated by space
Latitude Longitude: 28.6140 77.2091

Location validated successfully!
Attendance marked for Pawan Joshi (Roll 101)
Your location: (28.614000, 77.209100)
Returning to main menu...
```

## 📁 Data Files

### students.txt
```
101,Pawan Joshi
102,Anushka Goel
103,Jasmine Mahajan
104,Aaditya Uniyal
```

### sessions.txt (auto-generated)
```
A2B9X7K1 1728292830
```

### attendance_log.txt (auto-generated)
```
Roll: 101, Name: Pawan Joshi, Time: 2024-10-07 14:30:25, Location: (28.614000, 77.209100), Status: Present
```

## 🔧 Configuration

### Classroom Location
- **Default**: New Delhi coordinates (28.6139, 77.2090)
- **Radius**: 100 meters (0.1 km)
- **Modify**: Edit `setClassroomLocation()` in `main.c`

### Token Settings
- **Length**: 8 characters (alphanumeric)
- **Validity**: 30 seconds (configurable in `teacherMenu()`)
- **Format**: Uppercase letters and numbers

## 🧪 Testing the System

### Valid Test Cases:
1. **Roll Numbers**: 101, 102, 103, 104
2. **Valid Locations**: 
   - 28.6139 77.2090 (exact classroom)
   - 28.6140 77.2091 (nearby)
   - 28.6138 77.2089 (nearby)

### Invalid Test Cases:
1. **Invalid Roll**: 999
2. **Expired Token**: Wait 31+ seconds after generation
3. **Wrong Location**: 0.0 0.0 or distant coordinates

## 🐛 Troubleshooting

### Common Issues:

1. **"Student not found"**
   - Check if roll number exists in `data/students.txt`
   - Ensure file path is correct

2. **"Invalid or expired token"**
   - Generate new token from teacher menu
   - Ensure token is entered within 30 seconds

3. **"Location outside classroom range"**
   - Use coordinates near 28.6139 77.2090
   - Check if location validation radius is appropriate

### Build Issues:

1. **GCC not found**: Install MinGW or TDM-GCC on Windows
2. **Math library error**: Ensure `-lm` flag is included
3. **Header not found**: Check include paths with `-I./core`

## 🔮 Future Enhancements

- Web-based interface
- Database integration (SQLite/MySQL)
- Real-time GPS tracking
- Mobile app development
- Multi-classroom support
- Attendance analytics and reporting

## 📄 License

This project is part of the ARTAMS attendance management system development.

---

**Author**: Pawan Joshi  
**Version**: 1.0  
**Last Updated**: October 2025
