#include "../include/conf.h"
#include "../include/prediction_d.h"

int main(int argc, char *argv[]) {

	Conf c;
	DEWMA d;
	
	/* Path of the AP data file */
	const char *curr_data_file;
	const char *next_data_file;

	/* IDs of the current AP and the next AP */
	const char *curr_AP_id;
	const char *next_AP_id;

	/* DEWMA parameters */
	double alpha;
	double gamma;

	if(argc != 7) {
		cerr << "Error: wrong command" << endl;
		cout << "Command: ./shs curr_AP_id next_AP_id curr_AP_data_file next_AP_data_file alpha gamma" << endl;
		exit(1);
	}

	curr_AP_id = argv[1];
	next_AP_id = argv[2];

	curr_data_file = argv[3];	
	next_data_file = argv[4];

	alpha = atof(argv[5]);
	gamma = atof(argv[6]);

	c.read_curr_AP(curr_data_file);
	c.read_next_AP(next_data_file);

	d.curr_forecast(curr_AP_id, alpha, gamma);	
	d.next_forecast(next_AP_id, alpha, gamma);
}
