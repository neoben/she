#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <strings.h> 
#include <cstring>
#include <vector>

/* Maximum lenght of each line of the AP data file */
#define MAX_LINE_LEN 50 

using namespace std;

/* Parameters of the current AP (connected to the mobile node) */
struct curr_AP {
	double timestamp;	// Timestamp value
	double rssi;		// RSSI value
};

/* Parameters of the next AP */ 
struct next_AP {
	double timestamp;       // Timestamp value
        double rssi;            // RSSI value
};


/* Vector containing the parameters of the current AP */
extern vector <curr_AP> vc;

/* Vector containing the parameters of the next AP */
extern vector <next_AP> vn;

class Conf {
public:
	/* Constructor */
	Conf();	
	
	/* Read the parameters of the current AP from the (current) AP data file */
	void read_curr_AP(const char *data_file);

	/* Read the parameters of the next AP from the (next) AP data file */
        void read_next_AP(const char *data_file);

	/* Put the parameters of the current AP in a vector */ 
	void ins_curr_AP(char *timestamp, char *rssi);
	
	/* Put the parameters of the next AP in a vector */
	void ins_next_AP(char *timestamp, char *rssi);

};




