#include "location_validator.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static double class_lat = 0.0;
static double class_lon = 0.0;

#define MAX_RADIUS_KM 0.1
#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6372.0
#define CLASSROOM_FILE "data/classroom.txt"

static double toRadians(double degree) {
    return degree * (PI / 180.0);
}

static double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = sin(dLat / 2) * sin(dLat / 2) + cos(lat1) * cos(lat2) *sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return EARTH_RADIUS_KM * c;
}

void setClassroomLocation(double lat, double lon) {
    class_lat = lat;
    class_lon = lon;
    
    // Save to file for cross-process sharing
    FILE* file = fopen(CLASSROOM_FILE, "w");
    if (file) {
        fprintf(file, "%.6f %.6f\n", lat, lon);
        fclose(file);
    }
}

void loadClassroomLocation() {
    FILE* file = fopen(CLASSROOM_FILE, "r");
    if (file) {
        if (fscanf(file, "%lf %lf", &class_lat, &class_lon) != 2) {
            // Failed to read, keep defaults (0, 0)
            class_lat = 0.0;
            class_lon = 0.0;
        }
        fclose(file);
    }
    // If file doesn't exist, defaults remain (0, 0)
}

void getCurrentClassroomLocation(double* lat, double* lon) {
    // Load from file if not set in memory
    if (class_lat == 0.0 && class_lon == 0.0) {
        loadClassroomLocation();
    }
    *lat = class_lat;
    *lon = class_lon;
}

int validateLocation(double lat, double lon) {
    // Ensure classroom location is loaded from file
    if (class_lat == 0.0 && class_lon == 0.0) {
        loadClassroomLocation();
    }
    
    double distance = haversineDistance(class_lat, class_lon, lat, lon);
    if (distance <= MAX_RADIUS_KM) {
        return 1;
    } else {
        return 0; 
    }
}

double getDistanceFromClassroom(double lat, double lon) {
    // Ensure classroom location is loaded from file
    if (class_lat == 0.0 && class_lon == 0.0) {
        loadClassroomLocation();
    }
    return haversineDistance(class_lat, class_lon, lat, lon);
}

