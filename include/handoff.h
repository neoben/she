#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <strings.h> 
#include <cstring>
#include <vector>

class Handoff {
public:
	/* Constructor */
	Handoff();
	
	/* Sort in chronological order the values of the current AP and the next AP to check the handoff conditions */
	void start(const char *curr_AP_id, const char *next_AP_id, double beta, double gamma_g, double gamma_b);

	/* Check the conditions to trigger the handoff */
	void check(const char *curr_AP_id, const char *next_AP_id, double beta, double gamma_g, double gamma_b, double now, double RSSI_curr, double RSSI_next);
	/* Save the handoff instants in a file and switch from current AP to next AP */
	void do_handoff(double now, char *filename);
};
