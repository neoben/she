#include "../include/handoff.h"
#include "../include/smoothing.h"

/* Check when to switch AP after the Handoff */
int switch_AP;

Handoff::Handoff() {
 return;
}

void Handoff::start(const char *curr_AP_id, const char *next_AP_id, double beta, double gamma_g, double gamma_b) {
	
	double b;
	double gg;
	double gb;

	int len_c;
	int len_n;
	int len_tot;
	double now;
	double RSSI_curr;
	double RSSI_next;
	int index_c;
	int index_n;
	int count;

	const char *c;
	const char *n;

	switch_AP = 0; // Initialize the switch_AP variable

	c = curr_AP_id;
	n = next_AP_id;	

	/* Threshold beta to distinguish the two operating regions:
	* - hight-quality channel conditions
	* - low-quality channel conditions
	*/
	b = beta;

	gg = gamma_g;	// hysteresys threshold in case of hight-quality channel conditions
	gb = gamma_b;	// hysteresys threshold in case of low-quality channel conditions

	len_c = vsc.size();	// number of values of the current AP
	len_n = vsn.size();	// number of values of the next AP

	/* Initialize the value of index_c */
	index_c = 0;
        
	/* Initialize the value of index_n */
	index_n = 0;

	/* Initialize the value of now */
	now = 0;	

	/* Find the total length of the two (AP) vectors containing the RSSI values */
	len_tot = len_c + len_n;
	
	/* Initialize the counter variable used to browse the vectors */
	count = 0;

	/* Initialize the variable that checks when to switch from the current AP to the next AP */
	switch_AP = 0;

	/* DO NOT TOUCH...it works fine this way */
	while(true) { 

		/* Checked all the elements of the (current AP/next AP) vectors. Go out this damned loop */	
		if(count == len_tot)
			break;

		/* Checked all the elements of the current AP vector. Browse the next AP vector */
		if(index_c == len_c) {
			now = vsn[index_n].timestamp;

			if((switch_AP % 2) == 0) {
				RSSI_curr = vsc[index_c].rssi;
				RSSI_next = vsn[index_n].rssi;
			}
			else {
				RSSI_curr = vsn[index_n].rssi;
				RSSI_next = vsc[index_c].rssi;
			}

			check(c, n, b, gg, gb, now, RSSI_curr, RSSI_next);	

			index_n++;
			count++;
			continue;
		}

		/* Checked all the elements of the next AP vector. Browse the current AP vector */
		if(index_n == len_n) {
			now = vsc[index_c].timestamp;

			if((switch_AP % 2) == 0) {
                                RSSI_curr = vsc[index_c].rssi;
                                RSSI_next = vsn[index_n].rssi;
                        }
                        else {
                                RSSI_curr = vsn[index_n].rssi;
                                RSSI_next = vsc[index_c].rssi;
                        }
	                      
                        check(c, n, b, gg, gb, now, RSSI_curr, RSSI_next);

			index_c++;
			count++;
			continue;
		}

		if(vsc[index_c].timestamp <= vsn[index_n].timestamp && vsc[index_c].timestamp >= now) {
			now = vsc[index_c].timestamp;

			if((switch_AP % 2) == 0) {
                                RSSI_curr = vsc[index_c].rssi;
                                RSSI_next = vsn[index_n].rssi;
                        }
                        else {
                                RSSI_curr = vsn[index_n].rssi;
                                RSSI_next = vsc[index_c].rssi;
                        }
			
                        check(c, n, b, gg, gb, now, RSSI_curr, RSSI_next);

			index_c++;
			count++;
			continue;
		}

		if(vsn[index_n].timestamp <= vsc[index_c].timestamp && vsn[index_n].timestamp >= now) {
			now = vsn[index_n].timestamp;

          		if((switch_AP % 2) == 0) {
                                RSSI_curr = vsc[index_c].rssi;
                                RSSI_next = vsn[index_n].rssi;
                        }
                        else {
                                RSSI_curr = vsn[index_n].rssi;
                                RSSI_next = vsc[index_c].rssi;
                        }

                        check(c, n, b, gg, gb, now, RSSI_curr, RSSI_next);
		
			index_n++;
			count++;
			continue;
		}

	}
}

void Handoff::check(const char *curr_AP_id, const char *next_AP_id, double beta, double gamma_g, double gamma_b, double now, double RSSI_curr, double RSSI_next) {

	/* Set the file name */
        char filename[60];
        char path[] = "./data/";
        strcpy(filename, path);
        strcat(filename, curr_AP_id);
        strcat(filename, "_");
        strcat(filename, next_AP_id);
        strcat(filename, "_");
        strcat(filename, "handoff.dat");

	if(RSSI_curr >= beta) {
		if(RSSI_next >= (RSSI_curr + gamma_g)) {
			do_handoff(now, filename);
		}
	}
	else {
		if(RSSI_next >= (RSSI_curr + gamma_b)) {
			 do_handoff(now, filename);
		}
	}
}

void Handoff::do_handoff(double now, char *filename) {
	
	ofstream f(filename, ios::app);
        if(!f) {
                cerr << "Error: can not create the file " << filename << endl;
                return;
        }

	f << now << '\n';

	cout << "Handoff Trigger at timestamp: " << now << endl;

	/* Handoff triggered:
	*  switch the AP (current becomes next and next becomes current )
	*/
     	switch_AP++;

	f.close();
}
