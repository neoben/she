CC = g++
CFLAGS = -Wall -Werror

SOURCES1 = ./src/conf.cpp ./src/smoothing.cpp ./src/handoff.cpp ./src/shs.cpp
OUT1 = ./bin/shs

SOURCES2 = ./src/conf.cpp ./src/prediction_d.cpp ./src/shs_d_choose.cpp
OUT2 = ./bin/shs_d_choose

SOURCES3 = ./src/conf.cpp ./src/prediction_d.cpp ./src/shs_d.cpp
OUT3 = ./bin/shs_d

all:	shs shs_d_choose shs_d

shs: 	$(SOURCES1)
	$(CC) $(CFLAGS) -o $(OUT1) $(SOURCES1)

shs_d_choose:	$(SOURCES2)
	$(CC) $(CFLAGS) -o $(OUT2) $(SOURCES2)

shs_d:	$(SOURCES3)
	$(CC) $(CFLAGS) -o $(OUT3) $(SOURCES3)
 
clean:
	rm -f shs
	rm -f shs_d
	rm -rf $(OUT1)
	rm -rf $(OUT2)
	rm -rf $(OUT3)
	rm -f *.o core	
