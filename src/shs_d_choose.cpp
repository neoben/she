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
	const char *a;
	const char *g;

	/* Window to choose alpha and beta parameters */
	int window;
	const char *w;

	if(argc != 8) {
		cerr << "Error: wrong command" << endl;
		cout << "Command: ./shs curr_AP_id next_AP_id curr_AP_data_file next_AP_data_file alpha gamma window" << endl;
		exit(1);
	}

	curr_AP_id = argv[1];
	next_AP_id = argv[2];

	curr_data_file = argv[3];	
	next_data_file = argv[4];

	a = argv[5];
	g = argv[6];
	alpha = atof(argv[5]);
	gamma = atof(argv[6]);

	w = argv[7];
	window = atoi(argv[7]);

	c.read_curr_AP(curr_data_file);
	c.read_next_AP(next_data_file);

	d.curr_forecast(curr_AP_id, alpha, gamma);	
	d.next_forecast(next_AP_id, alpha, gamma);

	d.do_curr_forecast(window);
	d.write_do_curr_forecast(curr_AP_id, a, g, w);
	
	d.do_next_forecast(window);	
	d.write_do_next_forecast(next_AP_id, a, g, w);	

	/* Uncomment this function if you need to calculate the MSE value (or values) 
	*  Set the parameter 'use_window' of the 'prediction.cpp' file to FALSE
	*/
	d.MSE();
}
