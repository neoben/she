#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <strings.h> 
#include <cstring>
#include <vector>

using namespace std;

/* Smoothed parameters of the current AP (connected to the mobile node) */
struct s_curr_AP {
	double timestamp;	// Timestamp value
	double rssi;		// RSSI value
};

/* Smoothed parameters of the next AP */
struct s_next_AP {
        double timestamp;       // Timestamp value
        double rssi;            // RSSI value
};

/* Vector containing the smoothed parameters of the current AP */
extern vector <s_curr_AP> vsc;

/* Vector containing the smoothed parameters of the next AP */
extern vector <s_next_AP> vsn;

class EWMA {
public:
	/* Constructor */
	EWMA();
	
	/* Smooth the RSSI values of the current AP and put them in a vector */	
	void curr_smoothing(const char *c_AP_id, double alpha_p);
		
	/* Smooth the RSSI values of the next AP and put them in a vector */
        void next_smoothing(const char *n_AP_id, double alpha_p);

	/* Write a file.dat with the smoothed values of the current AP */
	void write_c_file(const char *c_AP_id);

	/* Write a file.dat with the smoothed values of the next AP */
        void write_n_file(const char *n_AP_id);

};
