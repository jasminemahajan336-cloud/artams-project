#include "location_validator.h"
#include <math.h> 

static double class_lat = 0.0;
static double class_lon = 0.0;

#define MAX_RADIUS_KM 0.1
#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6372.0

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
}

int validateLocation(double lat, double lon) {
    
    double distance = haversineDistance(class_lat, class_lon, lat, lon);
    if (distance <= MAX_RADIUS_KM) {
        return 1;
    } else {
        return 0; 
    }
}

