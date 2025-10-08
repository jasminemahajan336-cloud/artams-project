# ARTAMS - Attendance Management System (CLI Implementation)

This repository contains the core logic for the ARTAMS project, implemented as a standalone Command-Line Interface (CLI). This serves as our proof-of-concept for all backend functionality including token-based authentication, location validation, and attendance logging.

## 🏗 Project Structure

```
artams-project/
├── cli/
│   └── main.c              # Main CLI interface and navigation
├── core/
│   ├── student_db.c/.h     # Student database with hash table
│   ├── token_manager.c/.h  # Token generation and validation
│   ├── log_manager.c/.h    # Attendance logging system
│   ├── location_validator.c/.h # GPS location validation
│   └── utils.c/.h          # Utility functions
├── data/
│   ├── students.txt        # Pre-populated student database
│   ├── sessions.txt        # Active session tokens
│   └── attendance_log.txt  # Attendance records
├── Makefile               # Build automation (Linux/Mac)
├── run.bat               # Build and run (Windows)
├── clean.bat            # Clean build files (Windows)
└── README.md            # This file
```

## 🚀 How to Build and Run

### Windows (Recommended)

1. **Quick Start**: Double-click `run.bat` - this will automatically build and run the program.

2. **Manual Build**:
   ```cmd
   gcc -Wall -Wextra -std=c99 -I./core core/*.c cli/*.c -o artams_cli -lm
   artams_cli.exe
   ```

### Linux/Mac

1. **Using Make**:
   ```bash
   make
   ./artams_cli
   ```

2. **Manual Build**:
   ```bash
   gcc -Wall -Wextra -std=c99 -I./core core/*.c cli/*.c -o artams_cli -lm
   ./artams_cli
   ```

## 🎯 Features Implemented

### ✅ Core Functionality
- **Student Database**: Hash table-based student lookup system
- **Token Management**: Secure token generation with expiry validation
- **Location Validation**: GPS-based attendance verification (100m radius)
- **Attendance Logging**: Comprehensive attendance record keeping
- **CLI Navigation**: User-friendly teacher and student interfaces

### ✅ Security Features
- Time-limited session tokens (30 seconds default)
- Location-based attendance verification
- Student identity validation
- Secure file-based data storage

## 📱 How to Use

### Teacher Workflow:
1. Run the program and select **Teacher Mode (1)**
2. Choose **"Start Attendance Session (1)"**
3. A secure token will be generated and displayed (valid for 30 seconds)
4. Share this token with students for attendance marking
5. Use **"View Attendance Log (2)"** to see all attendance records

### Student Workflow:
1. Run the program and select **Student Mode (2)**
2. Enter your **Roll Number** (must exist in students database)
3. Enter the **token** provided by teacher
4. Enter your **GPS coordinates** (latitude longitude)
   - For testing: Use coordinates near `28.6139 77.2090` (classroom location)
   - Must be within 100 meters of classroom
5. System validates all inputs and marks attendance if successful

## 📊 Sample Usage

### Teacher Session:
```
=== ARTAMS - Attendance Management System ===
Select mode: (1) Teacher  (2) Student: 1

[Teacher Menu]
1. Start Attendance Session
2. View Attendance Log
3. Exit
> 1

✅ Session started!
🔑 Token: A2B9X7K1 (valid for 30 seconds)
📍 Students must be within 100m of classroom location
```

### Student Session:
```
=== ARTAMS - Attendance Management System ===
Select mode: (1) Teacher  (2) Student: 2

=== Student Attendance Marking ===
Enter Roll No: 101
✅ Student found: Pawan Joshi
Enter Token: A2B9X7K1
✅ Token validated successfully!
Enter Location (latitude longitude): 
[Hint: Try coordinates near 28.6139 77.2090 for valid location]
Latitude Longitude: 28.6140 77.2091
✅ Location validated successfully!
🎉 Attendance marked successfully for Pawan Joshi (Roll 101)!
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
**Last Updated**: October 2024
