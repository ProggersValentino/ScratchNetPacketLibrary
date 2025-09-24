#include "pch.h"
#include "Snapshot.h"
#include <bit>
#include "PacketSerialization.h"

SNPSHT_API Snapshot* CreateEmptySnapShot()
{
	return new Snapshot();
}

SNPSHT_API Snapshot* CreateFilledSnapShot(int id, float pX, float pY, float pZ)
{
	return new Snapshot(id, pX, pY, pZ);
}

SNPSHT_API void CompareSnapShot(Snapshot source, Snapshot target, std::vector<EVariablesToChange>& changedVariables, std::vector<char>& changes)
{
	float positionXDiffernce = target.posX - source.posX;
	float positionYDiffernce = target.posY - source.posY;
	float positionZDiffernce = target.posZ - source.posZ;

	if (positionXDiffernce > 0.002 || positionXDiffernce < -0.002) //how much tolerance are we willing to take on for imprecision
	{
		changedVariables.push_back(EVariablesToChange::positionX);

		SerializeFloat(positionXDiffernce, changes); //serialize the float into big endian and byte format
	}

	if (positionYDiffernce > 0.002 || positionYDiffernce < -0.002)
	{
		changedVariables.push_back(EVariablesToChange::positionY);

		SerializeFloat(positionYDiffernce, changes); //serialize the float into big endian and byte format
	}


	if (positionZDiffernce > 0.002 || positionZDiffernce < -0.002)
	{
		changedVariables.push_back(EVariablesToChange::positionZ);

		SerializeFloat(positionXDiffernce, changes); //serialize the float into big endian and byte format
	}
}
