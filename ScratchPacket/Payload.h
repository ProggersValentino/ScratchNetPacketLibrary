#pragma once
#include "Snapshot.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <bitset>

#define PLOAD_EXPORTS

#ifdef PLOAD_EXPORTS
#define PLOAD_API __declspec(dllexport)
#else
#define PLOAD_API __declspec(dllimport)
#endif

/// <summary>
/// this struct is another key componenet to our delta compression method where we will take the data that has been collected 
/// and translate it to a bit mask for the reciever to determine which variables will get changed and compress the changed values so that they are ready to be sent over 
/// the network with as little bandwidth as possible
/// </summary>
struct PLOAD_API Payload
{
	uint8_t bitMask;

	std::vector<char> setChanges;

	Payload(): bitMask(0b00000000) {}

	//when the data for the payload is fed through it gets convertted & compressed for to send over the network
	Payload(std::vector<EVariablesToChange> variablesMasks, std::vector<char>& changedValues) : bitMask(0b00000000)
	{
		UpdateMasks(variablesMasks);

		setChanges.resize(changedValues.size());

		//copy value over 
		for (int i = 0; i < setChanges.size(); i++) 
		{
			setChanges[i] = changedValues[i];
		}
		
			
		//memcpy(&setChanges, changedValues.data(), changedValues.size());
	}

	void UpdateMasks(std::vector<EVariablesToChange>& masks) 
	{
		//creating the bitmask to determine which variables will get changed
		for (int i = 0; i < masks.size(); i++)
		{
			switch (masks[i])
			{
			case EVariablesToChange::positionX:
				bitMask |= 0b00000001;
				break;

			case EVariablesToChange::positionY:
				bitMask |= 0b00000010;
				break;

			case EVariablesToChange::positionZ:
				bitMask |= 0b00000100;
				break;
			}

			std::cout << std::bitset<8>(bitMask) << std::endl;
		}
	}
};

extern "C" 
{
	PLOAD_API Payload* CreateEmptyPayload();
	PLOAD_API Payload* CreatePayload(std::vector<EVariablesToChange> masks, std::vector<char> changedValues);
}