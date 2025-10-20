#ifndef LOCATION_VALIDATOR_H
#define LOCATION_VALIDATOR_H

void setClassroomLocation(double lat, double lon);
void loadClassroomLocation();
int validateLocation(double lat, double lon);
void getCurrentClassroomLocation(double* lat, double* lon);
double getDistanceFromClassroom(double lat, double lon);

#endif 

