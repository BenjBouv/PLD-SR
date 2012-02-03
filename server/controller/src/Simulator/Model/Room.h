/*
 * Room.h
 *
 *  Created on: 1 févr. 2012
 *      Author: bill
 */

#ifndef ROOM_H_
#define ROOM_H_

using namespace std;
#include <pthread.h>
#include <vector>

class Room {
public:
	int getId();
	void addNeigthborRoom(Room* id);
	vector<Room*> getNeigthborRooms();

	float getTemperature();
	void setTemperature(float v);
	float getHumidity();
	void setHumidity(float v);
	float getCO2Level();
	void setCO2Level(float v);
	float getLuminosity();
	void setLuminosity(float v);
	bool getPIRStatus();
	void setPIRStatus(bool v);
	bool getOccupancy();
	void setOccupancy(bool v);

	Room(int id);
	virtual ~Room();

protected:
	int id;
	vector<Room*> neigthborRooms;

	float temperature;
	float humidity;
	float co2Level;
	float luminosity;
	bool pirStatus;
	bool occupancy;

	pthread_mutex_t mutex;
};

#endif /* ROOM_H_ */
