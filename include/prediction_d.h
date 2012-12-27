#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <strings.h> 
#include <cstring>
#include <vector>
#include <math.h>

using namespace std;

/* Smoothed parameters of the current AP (connected to the mobile node) */
struct spd_curr_AP {
	double timestamp;	// Timestamp value
	double rssi;		// RSSI value
};

/* Forecast parameters of the current AP (connected to the mobile node) */
struct pd_curr_AP {
	double timestamp;       // Timestamp value
        double rssi;            // RSSI value
};

/* Smoothed parameters of the next AP */
struct spd_next_AP {
        double timestamp;       // Timestamp value
        double rssi;            // RSSI value
};

/* Forecast parameters of the next AP */
struct pd_next_AP {
	double timestamp;       // Timestamp value
        double rssi;            // RSSI value
};

/* Vector containing the forecast parameters of the current AP */
extern vector <pd_curr_AP> vpdc;

/* Vector containing the forecast smoothed parameters of the current AP */
extern vector <spd_curr_AP> vspdc;

/* Vector containing the forecast parameters of the next AP */
extern vector <pd_next_AP> vpdn;

/* Vector containing the forecast smoothed parameters of the next AP */
extern vector <spd_next_AP> vspdn;

/* Forecast value and parameters */
struct param {
        double forecast;        // RSSI forecast  -> F(t+m) = S(t) + mb(t), m is the number of forecast step ahead 
	double timestamp;	// timestamp
};

/* Vector containing the forecast value for the current AP */
extern vector <param> cfp;

/* Vector containing the forecast value for the next AP */
extern vector <param> nfp;

class DEWMA {
public:
	/* Constructor */
	DEWMA();

	/* Find the appropriate alpha e beta parameters to use in the DEWMA filter*/
	void find_parameters();

	/* Forecast and smooth the RSSI values of the current AP and put them in a vector */
	void curr_forecast(const char *c_AP_id, double alpha_p, double gamma_p);

	/* Forecast and smooth the RSSI value of the next AP and put them in a vector */
	void next_forecast(const char *n_AP_id, double alpha_p, double gamma_p);	

	/* Perform the actual forecast fot the current AP  */
	void do_curr_forecast(int window);

	/* Perform the actual forecast fot the next AP  */
        void do_next_forecast(int window);

	/* Calculate the MSE between the observed data and the one step ahead forecast for the current AP */
	void MSE();	

	/* Write in append mode the current MSE value in file */
	void write_mse(double mse);
	
	/* Write a file.dat with the final forecast values of the current AP */
	void write_do_curr_forecast(const char *c_AP_id, const char* a, const char* g, const char* w);

	/* Write a file.dat with the final forecast values of the next AP */
        void write_do_next_forecast(const char *n_AP_id, const char* a, const char* g, const char* w);

};

