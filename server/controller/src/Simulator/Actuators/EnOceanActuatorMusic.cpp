/*************************************************************************
                           EnOceanActuatorMusic  -  description
                             -------------------
    Creation             : 28 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Thibaut PATEL (TPL)
*************************************************************************/

//---- Implementation - <EnOceanActuatorMusic> (EnOceanActuatorMusic.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <iostream>
#include <cstdlib>
//------------------------------------------------------ Personnal Include
#include "EnOceanActuatorMusic.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods

float EnOceanActuatorMusic::getPower() {
	return 0;
}

void EnOceanActuatorMusic::setPower(float e) {
}

float EnOceanActuatorMusic::update() {
	return 0;
}

void EnOceanActuatorMusic::set(enocean_data_structure* frame)  {
	pthread_mutex_lock(&mutex);
	on = (frame->DATA_BYTE0 >> 3) & 1;
	if (on) {
		system("chromium-browser http://www.youtube.com/watch?v=l-dYNttdgl0");
	}
	pthread_mutex_unlock(&mutex);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
EnOceanActuatorMusic::EnOceanActuatorMusic(int i, float e): EnOceanActuator(i,e){
	cout << "<Actuator Simu n°" << id << "> Music - Created\n";
} //----- End of EnOceanActuatorMusic

EnOceanActuatorMusic::~EnOceanActuatorMusic() {
	// TODO Auto-generated destructor stub

} //----- End of ~EnOceanActuatorMusic


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
