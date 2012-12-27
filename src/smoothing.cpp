#include "../include/smoothing.h"
#include "../include/conf.h"

/* Vector containing the smoothed parameters of the current AP */
vector <s_curr_AP> vsc;

/* Vector containing the smoothed parameters of the next AP */
vector <s_next_AP> vsn;

EWMA::EWMA() {
	/* Clear the data structures */
	vsc.clear();
	vsn.clear();
	return;
}

void EWMA::curr_smoothing(const char *c_AP_id, double alpha_p) {
	
	int len;
	double alpha;
	double time;
	double rssi;
	double s_old;
	double s;

	s_curr_AP sca;

	/*	EWMA Filter Implementation:
	*
	*  	- Smoothed_RSSI(0) = RSSI(0)
	* 
	*	 Smoothed_RSSI(t) = aplha * RSSI(t) + (1 - alpha) * Smoothed_RSSI(t-1)
	*/

	len = vc.size(); 	// number of rssi values for the current AP (vector length)
	alpha = alpha_p;	// set the alpha parameter
	s_old = vc[0].rssi;	// initialize the s_old value -> Smoothed_RSSI(0) = RSSI(0)

	for(int i = 0; i < len; i++) {

		rssi = vc[i].rssi;
		time = vc[i].timestamp;

		s = alpha * rssi + (1 - alpha) * s_old;

		sca.timestamp = time;
		sca.rssi = s;
		vsc.push_back(sca);

		s_old = s;
	}

	write_c_file(c_AP_id);
}

void EWMA::next_smoothing(const char *n_AP_id, double alpha_p) {

        int len;
        double alpha;
        double time;
        double rssi;
        double s_old;
        double s;

        s_next_AP sna;

        /*      EWMA Filter Implementation:
        *
        *       - s_old(0) = rssi(0)
        * 
        *        Smoothed_RSSI(t) = aplha * RSSI(t) + (1 - alpha) * Smoothed_RSSI(t-1)
        */

        len = vn.size();        // number of rssi values for the next AP (vector length)
        alpha = alpha_p;       	// set the alpha parameter
        s_old = vn[0].rssi;     // initialize the s_old value -> Smoothed_RSSI(0) = RSSI(0)

        for(int i = 0; i < len; i++) {

                rssi = vn[i].rssi;
                time = vn[i].timestamp;

                s = alpha * rssi + (1 - alpha) * s_old;

                sna.timestamp = time;
                sna.rssi = s;
                vsn.push_back(sna);
                s_old = s;
        }

	write_n_file(n_AP_id);

}

void EWMA::write_c_file(const char *c_AP_id) {

	int len;

	/* Set the file name */
	char filename[50];
	char path[] = "./data/";
	strcpy(filename, path);
	strcat(filename, c_AP_id);
	strcat(filename, "_smo.dat");

	fstream f(filename, ios::out);
	if(!f) {
		cerr << "Error: can not create the file " << filename << endl;
                return;
	}	

	len = vsc.size();	// number of lines of the new file

	for(int i = 0; i < len; i++) {
		f << vsc[i].timestamp << " " << vsc[i].rssi << "\n";
	}

	f.close();
}

void EWMA::write_n_file(const char *n_AP_id) {
	
        int len;

	/* Set the file name */
        char filename[50];
	char path[] = "./data/";
        strcpy(filename, path);
        strcat(filename, n_AP_id);
        strcat(filename, "_smo.dat");

        fstream f(filename, ios::out);
        if(!f) {
                cerr << "Error: can not create the file " << filename << endl;
                return;
        }

        len = vsn.size();       // number of lines of the new file

        for(int i = 0; i < len; i++) {
                f << vsn[i].timestamp << " " << vsn[i].rssi << "\n";
        }

	f.close();
}
