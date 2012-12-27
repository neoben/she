#include "../include/prediction_d.h"
#include "../include/conf.h"

/* Vector containing the forecast smoothed parameters of the current AP */
vector <spd_curr_AP> vspdc;

/* Vector containing the forecast parameters of the current AP */
vector <pd_curr_AP> vpdc;

/* Vector containing the forecast parameters of the next AP */
vector <pd_next_AP> vpdn;

/* Vector containing the forecast smoothed parameters of the next AP */
vector <spd_next_AP> vspdn;

/* Vector containing the forecast value for the current AP */
vector <param> cfp;

/* Vector containing the forecast value for the next AP */
vector <param> nfp;

DEWMA::DEWMA() {
	/* Clear the data structures */
	vspdc.clear();
	vpdc.clear();
	vpdn.clear();
	vspdn.clear();
	cfp.clear();
	nfp.clear();
	return;
	}

void DEWMA::curr_forecast(const char *c_AP_id, double alpha_p, double gamma_p) {
	
	int len;
	double alpha;
	double gamma;
	double time;
	double rssi;
	double s_old;
	double b_old;
	double s;
	double b;

	spd_curr_AP spdca;
	pd_curr_AP pdca;	

	/*	DEWMA Filter Implementation:
	*
	*  	- S(0) = rssi(0)
	*	- B(0) = [rssi(n) - rssi(0)] / (n - 1)
	* 
	*	S(t) = aplha * RSSI(t) + (1 - alpha) * (S(t-1) + B(t))
	*	B(t) = gamma * (S(t) + S(t-1)) + (1 - gamma) * B(t-1)
	*/ 

	len = vc.size();	// number of rssi values for the current AP (vector length)
	alpha = alpha_p;	// set the alpha parameter
        gamma = gamma_p;	// set the gamma parameter
	s_old = vc[0].rssi;					// initialize the s_old value => S(0) = RSSI(0)	
	b_old = (vc[len].rssi - vc[0].rssi) / (len - 1);	// initialize the b_old value => B(0) = [RSSI(n) - RSSI(0)]/(n - 1) 

	for(int i = 0; i < len; i++) {
		
		rssi = vc[i].rssi;
		time = vc[i].timestamp;	

		s = alpha * rssi + (1 - alpha) * (s_old + b_old);
		
		b = gamma * (s - s_old) + (1 - gamma) * b_old;

		spdca.timestamp = time;
		spdca.rssi = s;
		vspdc.push_back(spdca);

		pdca.timestamp = time;
                pdca.rssi = b;
                vpdc.push_back(pdca);

		s_old = s;
		b_old = b;
		
	}	

}

void DEWMA:: next_forecast(const char *n_AP_id, double alpha_p, double gamma_p) {

	int len;
        double alpha;
        double gamma;
        double time;
        double rssi;
        double s_old;
        double b_old;
        double s;
        double b;

	spd_next_AP spdna;
        pd_next_AP pdna;

	/*      DEWMA Filter Implementation:
        *
        *       - S(0) = rssi(0)
        *       - B(0) = [rssi(n) - rssi(0)] / (n - 1)
        * 
        *       S(t) = aplha * RSSI(t) + (1 - alpha) * (S(t-1) + B(t))
        *       B(t) = gamma * (S(t) + S(t-1)) + (1 - gamma) * B(t-1)
        */

        len = vn.size();        // number of rssi values for the current AP (vector length)
        alpha = alpha_p;        // set the alpha parameter
        gamma = gamma_p;        // set the gamma parameter
        s_old = vn[0].rssi;                                     // initialize the s_old value => S(0) = RSSI(0) 
        b_old = (vn[len].rssi - vn[0].rssi) / (len - 1);        // initialize the b_old value => B(0) = [RSSI(n) - RSSI(0)]/(n - 1) 

	for(int i = 0; i < len; i++) {

                rssi = vn[i].rssi;
                time = vn[i].timestamp;

                s = alpha * rssi + (1 - alpha) * (s_old + b_old);

                b = gamma * (s - s_old) + (1 - gamma) * b_old;

                spdna.timestamp = time;
                spdna.rssi = s;
                vspdn.push_back(spdna);

                pdna.timestamp = time;
                pdna.rssi = b;
                vpdn.push_back(pdna);

                s_old = s;
                b_old = b;

        }	

}

/* I apologize for this part of the code: it's a real mess, but it is what I needed */

void DEWMA::do_curr_forecast(int window) {

        double f;

	int len1 = window;
	int len2 = vc.size();

	int diff;

	double last_timestamp;	// last timestamp before forecasting
	int lt_index;		// last timestamp index
	int nt_index;		// next timestamp index

	double timestamp;
	double rssi;
	double forecast;

	double s;
	double b;

	int m;			// Number of step ahead

	/*  EDIT THIS VARIABILE TO USE OR NOT THE WINDOW PARAMETER */
	bool use_window = false;

	param p;

	/* Check the size of the window */
	if(window >= (int)vc.size()) {
		cerr << "Error: the window parameter must be smaller than the size of the observed data" << endl;
		exit(1);
	}

	if(use_window == false) { // Do the one step ahead forecast using all the observed values

		cout << endl;
		cout << "Current AP: Window Parameter NOT IN USE" << endl;
		cout << endl;

		len1 = NULL;    // Clean the len variable not in use
		m = 1;
		
        	for(int i = 0; i < len2; i++) {

               		f = vspdc[i].rssi + (m * vpdc[i].rssi);
		
			p.forecast = f;
			p.timestamp = vspdc[i].timestamp;

			cfp.push_back(p);
        	}
	}
	else if(use_window == true) {  // Do the m step ahead forecast using (observed_data_size - window) values

		cout << endl;
                cout << "Current AP: Window Parameter IN USE" << endl;
                cout << endl;

		int j = 0;
		while(true) {
			last_timestamp = vc[j].timestamp;
			if(last_timestamp >= window) {
				last_timestamp = vc[j-1].timestamp;
				lt_index = j - 1;
				nt_index = j;
				break;
			}
			else {
				j++;
			}
		}

		for(int i = 0; i <= lt_index; i++) {

                	timestamp = vc[i].timestamp;
			rssi = vc[i].rssi;
			
			p.forecast = rssi;
                        p.timestamp = timestamp;

			cfp.push_back(p);
        	}

		diff = len2 - lt_index;

		s = vspdc[lt_index].rssi;
		b = vpdc[lt_index].rssi;
		
		for(int i = 1; i < diff; i++) {
			
			f = s + (i * b);
			
			timestamp = vc[lt_index + i].timestamp;
			forecast = f;
			 
			p.timestamp = timestamp;
			p.forecast = forecast;

			cfp.push_back(p);
		}
		
	}//endif (use_window = true)
}

void DEWMA::do_next_forecast(int window) {

        double f;

	int len1 = window;
	int len2 = vn.size();

	int diff;

	double last_timestamp;	// last timestamp before forecasting
	int lt_index;		// last timestamp index
	int nt_index;		// next timestamp index

	double timestamp;
	double rssi;
	double forecast;

	double s;
	double b;

	int m;			// Number of step ahead

	/*  EDIT THIS VARIABILE TO USE OR NOT THE WINDOW PARAMETER */
	bool use_window = false;

	param p;

	/* Check the size of the window */
	if(window >= (int)vn.size()) {
		cerr << "Error: the window parameter must be smaller than the size of the observed data" << endl;
		exit(1);
	}

	if(use_window == false) { // Do the one step ahead forecast using all the observed values

		cout << endl;
		cout << "Next AP: Window Parameter NOT IN USE" << endl;
		cout << endl;

		len1 = NULL;    // Clean the len variable not in use
		m = 1;
		
        	for(int i = 0; i < len2; i++) {

               		f = vspdn[i].rssi + (m * vpdn[i].rssi);
		
			p.forecast = f;
			p.timestamp = vspdn[i].timestamp;

			nfp.push_back(p);
        	}
	}
	else if(use_window == true) {  // Do the m step ahead forecast using (observed_data_size - window) values

		cout << endl;
                cout << "Next AP: Window Parameter IN USE" << endl;
                cout << endl;

		int j = 0;
		while(true) {
			last_timestamp = vn[j].timestamp;
			if(last_timestamp >= window) {
				last_timestamp = vn[j-1].timestamp;
				lt_index = j - 1;
				nt_index = j;
				break;
			}
			else {
				j++;
			}
		}

		for(int i = 0; i <= lt_index; i++) {

                	timestamp = vn[i].timestamp;
			rssi = vn[i].rssi;
			
			p.forecast = rssi;
                        p.timestamp = timestamp;

			nfp.push_back(p);
        	}

		diff = len2 - lt_index;

		s = vspdn[lt_index].rssi;
		b = vpdn[lt_index].rssi;
		
		for(int i = 1; i < diff; i++) {
			
			f = s + (i * b);
			
			timestamp = vn[lt_index + i].timestamp;
			forecast = f;
			 
			p.timestamp = timestamp;
			p.forecast = forecast;

			nfp.push_back(p);
		}
		
	}//endif (use_window = true)
}

void DEWMA::MSE() {
	
	double observed;
	double forecast;

	double diff = 0;
	double num = 0;
	double mse = 0;

        int len = vc.size();

	for(int i = 0; i < len; i++) {
		
		observed = vc[i].rssi;
		forecast = cfp[i].forecast;
		
		diff = observed - forecast;
		num += pow(diff, 2);

	}

	mse = num / len;

	write_mse(mse);	
}

void DEWMA::write_mse(double mse) {
	
	/* Set the file name */
        char filename[50];
        char path[] = "./data/";
        strcpy(filename, path);
        strcat(filename, "MSE.dat");

        ofstream f(filename, ios::app);
        if(!f) {
                cerr << "Error: can not create (or open in append mode) the file " << filename << endl;
                return;
        }

	f << mse << "\n";

	f.close();
}

void DEWMA::write_do_curr_forecast(const char *c_AP_id, const char* a, const char* g, const char* w) {

	/* Set the file name */
        char filename[70];
        char path[] = "./data/";
        strcpy(filename, path);
        strcat(filename, c_AP_id);
        strcat(filename, "_for_a");
	strcat(filename, a);
	strcat(filename, "_g");
	strcat(filename, g);
        strcat(filename, "_w");
	strcat(filename, w);
	strcat(filename, ".dat");

	int window = atoi(w);

	int len1 = window;
        int len2 = cfp.size();

	fstream f(filename, ios::out);
        if(!f) {
                cerr << "Error: can not create the file " << filename << endl;
                return;
        }

	len1 = NULL;	// Clean the len variable not in use

	for(int i = 0; i < len2; i++) {
		f << cfp[i].timestamp << " " << cfp[i].forecast << "\n";		
	}

	f.close();
}

void DEWMA::write_do_next_forecast(const char *n_AP_id, const char* a, const char* g, const char* w) {

	/* Set the file name */
        char filename[70];
        char path[] = "./data/";
        strcpy(filename, path);
        strcat(filename, n_AP_id);
        strcat(filename, "_for_a");
	strcat(filename, a);
	strcat(filename, "_g");
	strcat(filename, g);
        strcat(filename, "_w");
	strcat(filename, w);
	strcat(filename, ".dat");

	int window = atoi(w);

	int len1 = window;
        int len2 = nfp.size();

	fstream f(filename, ios::out);
        if(!f) {
                cerr << "Error: can not create the file " << filename << endl;
                return;
        }

	len1 = NULL;	// Clean the len variable not in use

	for(int i = 0; i < len2; i++) {
		f << nfp[i].timestamp << " " << nfp[i].forecast << "\n";		
	}

	f.close();
}
