#include "../include/conf.h"
#include "../include/smoothing.h"
#include "../include/handoff.h"

int main(int argc, char *argv[]) {

	Conf c;
	EWMA e;
	Handoff h;

	/* Path of the AP data file */
	const char *curr_data_file;
	const char *next_data_file;

	/* IDs of the current AP and the next AP */
	const char *curr_AP_id;
	const char *next_AP_id;

	/* Alpha parameter for the EWMA filter */
	double alpha;

	/* Handoff parameters */
	double beta;
	double gamma_g;
	double gamma_b;

	if(argc != 9) {
		cerr << "Error: wrong command" << endl;
		cout << "Command: ./shs curr_AP_id next_AP_id curr_AP_data_file next_AP_data_file alpha beta gamma_g gamma_b" << endl;
		exit(1);
	}

	curr_AP_id = argv[1];
	next_AP_id = argv[2];
	
	cout << endl;
	cout << "Handoff Simulation :: Hysteresis Algorithm" << endl;
	cout << endl;
	cout << "Access Point: " << curr_AP_id << endl;
	cout << "Access Point: " << next_AP_id << endl;
	cout << endl;

	curr_data_file = argv[3];	
	next_data_file = argv[4];	

	alpha = atof(argv[5]);

	beta = atof(argv[6]);
	gamma_g = atof(argv[7]);
	gamma_b = atof(argv[8]);

	c.read_curr_AP(curr_data_file);
	c.read_next_AP(next_data_file);

	e.curr_smoothing(curr_AP_id, alpha);
	e.next_smoothing(next_AP_id, alpha);

	h.start(curr_AP_id, next_AP_id, beta, gamma_g, gamma_b);
	
	cout << endl;
}

