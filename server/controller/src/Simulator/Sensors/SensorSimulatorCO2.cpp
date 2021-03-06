
/*************************************************************************
                           SensorSimulatorCO2  -  description
                             -------------------
    Creation             : 30 Jan. 2012
    Copyright            : (C) 2012 by H4311 - Benjamin PLANCHE (BPE)
*************************************************************************/

//---- Implementation - <SensorSimulatorCO2> (SensorSimulatorCO2.cpp file) -----

//---------------------------------------------------------------- INCLUDE

//--------------------------------------------------------- System Include
using namespace std;
#include <stdlib.h>
#include <iostream>
//------------------------------------------------------ Personnal Include
#include "SensorSimulatorCO2.h"
#include "../../Devices/EnOceanSensorAPI.h"
#include "../Model/Room.h"
//-------------------------------------------------------------- Constants

//----------------------------------------------------------------- PUBLIC

//--------------------------------------------------------- Public Methods
void SensorSimulatorCO2::update() {
	float co2L = 0;
	Room* room = dynamic_cast<Room*>(subject);
	if (room != 0) {
		co2L = room->getCO2Level();
	}
	if (co2L > ppmMax) { co2L = ppmMax; }
	else if (co2L < ppmMin) { co2L = ppmMin; }
	EnOceanSensorAPI::setCO2Level(&frame, co2L, ppmMin, ppmMax);
}

//------------------------------------------------- Static public Methods

//------------------------------------------------------------- Operators


//-------------------------------------------------- Builder / Destructor
SensorSimulatorCO2::SensorSimulatorCO2(int id, Subject* r, float minp, float maxp) : SensorSimulator(id, EnOceanSensorAPI::ORG_4BS, r), ppmMin(minp), ppmMax(maxp) {
	float t = 0;
	Room* room = dynamic_cast<Room*>(r);
	if (room != 0) {
		t = room->getCO2Level();
	} else { subject = NULL; }
	EnOceanSensorAPI::setCO2Level(&frame, t, ppmMin, ppmMax);
	cout << "<Sensor Simu n°" << id << "> Créé - " << t << "ppm [" << ppmMin << "; " << ppmMax << "]\n";

} //----- End of SensorSimulatorCO2

SensorSimulatorCO2::~SensorSimulatorCO2() {
} //----- End of ~SensorSimulatorCO2


//---------------------------------------------------------------- PRIVATE

//------------------------------------------------------ Protected Methods
