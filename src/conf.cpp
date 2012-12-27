#include "../include/conf.h"

/* Temporary string for each line of the AP data file */
char curr_l[MAX_LINE_LEN]; 	// current AP data file
char next_l[MAX_LINE_LEN];	// next AP data file

/* Vector containing the parameters of the current AP */
vector <curr_AP> vc;

/* Vector containing the parameters of the next AP */
vector <next_AP> vn;

Conf::Conf() {
	/* Clear the data structures */
	vc.clear();
	vn.clear();
	return;
}

void Conf::read_curr_AP(const char *data_file) {
	
	fstream f;
	char *tmp_t;
	char *tmp_r;

	f.open(data_file, ios::in);
	if(!f) {
		cerr << "Error: can not open the file " << data_file << endl;
		return;
	}

	while(f.getline(curr_l, MAX_LINE_LEN)) {
		
		/* Get the timestamp value from the file */ 	
		tmp_t = strtok(curr_l, " ");
		if(tmp_t == NULL) 
			continue;

		/* Get the rssi value from the file */
		tmp_r = strtok(NULL, " ");
		if(tmp_r == NULL)
			continue;

		ins_curr_AP(tmp_t, tmp_r);	
		
	}

	f.close();	
}

void Conf::read_next_AP(const char *data_file) {

        fstream f;
        char *tmp_t;
        char *tmp_r;

        f.open(data_file, ios::in);
        if(!f) {
                cerr << "Error: can not open the file " << data_file << endl;
                return;
        }

        while(f.getline(next_l, MAX_LINE_LEN)) {

                /* Get the timestamp value from the file */
                tmp_t = strtok(next_l, " ");
                if(tmp_t == NULL)
                        continue;

                /* Get the rssi value from the file */
                tmp_r = strtok(NULL, " ");
                if(tmp_r == NULL)
                        continue;

                ins_next_AP(tmp_t, tmp_r);
        }

        f.close();
}

void Conf::ins_curr_AP(char *timestamp, char *rssi) { 

        double t;
        double r;

        curr_AP ca;

        t = atof(timestamp);    // convert the timestamp value from char* to double
        r = atof(rssi);         // convert the rssi value from char* to double

        ca.timestamp = t;
        ca.rssi = r;
        vc.push_back(ca);
}

void Conf::ins_next_AP(char *timestamp, char *rssi) {
	
	double t;
	double r;

	next_AP na;

	t = atof(timestamp);	// convert the timestamp value from char* to double
	r = atof(rssi);		// convert the rssi value from char* to double

	na.timestamp = t;
	na.rssi = r;
	vn.push_back(na);
}
