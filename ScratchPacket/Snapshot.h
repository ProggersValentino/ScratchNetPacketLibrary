#pragma once
#include <iostream>
#include <vector>


#define SNPSHT_EXPORTS

#ifdef SNPSHT_EXPORTS
#define SNPSHT_API __declspec(dllexport)
#else
#define SNPSHT_API __declspec(dllimport)
#endif

enum EVariablesToChange 
{
	positionX, positionY, positionZ
};

struct SNPSHT_API Snapshot
{
	int objectId;
	float posX;
	float posY;
	float posZ;

	Snapshot() : objectId(0), posX(0.0f), posY(0.0f), posZ(0.0f) {}

	Snapshot(int id, float x, float y, float z) : objectId(id), posX(x), posY(y), posZ(z) {}

	
};  

//utility functions to create and edit a snapshot
extern "C" {

	SNPSHT_API Snapshot* CreateEmptySnapShot();

	SNPSHT_API Snapshot* CreateFilledSnapShot(int id, float pX, float pY, float pZ);

	//compare both snapshot variables and add changes to them if there is a difference -> this is one of steps needed for Delta Compression
	SNPSHT_API void CompareSnapShot(Snapshot source, Snapshot target, std::vector<EVariablesToChange>& changedVariables, std::vector<char>& changes);
}