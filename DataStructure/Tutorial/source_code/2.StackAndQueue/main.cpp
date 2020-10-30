#include"ParkingManager.h"

int main() {
	ParkingManager* pm = new ParkingManager();
	pm->mainLoop();
	delete pm;
	return 0;
}