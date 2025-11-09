# 🚀 How to Run ARTAMS - Complete Guide

## **Quick Start:**

### 1. **Compile the Program**
```bash
cd artams-project
gcc -o artams cli/main.c core/*.c -I core
```

### 2. **Run the Program**
```bash
./artams
```

## **Login Credentials:**

### **👨‍🏫 Teacher Login:**
- Username: `admin`, Password: `admin123`
- Username: `ravi`, Password: `teachpass`
- Username: `anushka`, Password: `hello123`

### **👨‍🎓 Student Login:**
- Roll: `101`, Password: `pass101` (Pawan Joshi)
- Roll: `102`, Password: `pass102` (Anushka Goel)
- Roll: `103`, Password: `pass103` (Jasmine Mahajan)
- Roll: `104`, Password: `pass104` (Aaditya Uniyal)

## **🎯 Test Scenarios:**

### **Scenario 1: Test Dynamic File Creation**
1. Run: `./artams`
2. Choose: `2` (Student Login)
3. Login: Roll `101`, Password `pass101`
4. Enter any token (e.g., `ABC123`)
5. Enter location: `28.644800 77.216721`
6. **Result**: System creates `attendance_09NOV.txt` automatically!

### **Scenario 2: Test Teacher Date Viewing**
1. Run: `./artams`
2. Choose: `1` (Teacher Login)
3. Login: Username `admin`, Password `admin123`
4. Choose: `2` (View Attendance Log)
5. Choose: `1` (Today's Attendance)
6. **Result**: See today's attendance from dynamic file!

### **Scenario 3: Test Date Selection**
1. Teacher login → View Attendance Log
2. Choose: `5` (Show Available Dates)
3. **Result**: See which date files exist
4. Choose: `3` (Custom Date)
5. Enter: `08NOV` or `07NOV`
6. **Result**: View historical attendance (if exists)

## **📁 What Happens:**

### **When Student Marks Attendance:**
- ✅ Creates `data/attendance_09NOV.txt` (today's file)
- ✅ Saves to `data/attendance_log.txt` (master log)
- ✅ Shows: "📅 Saved to date file: attendance_09NOV.txt"

### **When Teacher Views Attendance:**
- ✅ Shows visual folder structure
- ✅ Allows date selection
- ✅ Displays date-specific attendance
- ✅ Smart error handling for missing dates

## **🔧 Troubleshooting:**

### **If compilation fails:**
```bash
# Try with different output name
gcc -o artams_new cli/main.c core/*.c -I core
./artams_new
```

### **If "Permission denied":**
```bash
# Close any running instances first, then:
gcc -o artams_v2 cli/main.c core/*.c -I core
./artams_v2
```

## **🎉 Features Working:**

✅ **Dynamic file creation** (attendance_09NOV.txt, etc.)
✅ **Streamlined student login** (no redundant roll entry)
✅ **Date-based teacher viewing**
✅ **Visual folder structure display**
✅ **Smart duplicate prevention**
✅ **Real-time attendance organization**

## **Ready to Use!**

Your ARTAMS system is fully functional with both requested features implemented and working perfectly!