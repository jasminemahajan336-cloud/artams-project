#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

void markAttendance(const char* filename, int roll_no, const char* student_name, double lat, double lon, const char* status);
void showAttendance(const char* filename);

#endif 

