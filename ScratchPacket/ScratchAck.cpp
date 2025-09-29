#include "pch.h"
#include "ScratchAck.h"

PacketData* ScratchAck::GetPacketData(uint16_t providedSequence)
{
	const int index = providedSequence % bufferSize;

	//has the provided sequence been recorded?
	if (sequence_buffer[index] == providedSequence)
	{
		return &packet_data[index]; //return the packet data in relation to this sequence
	}
	else {
		return NULL; //else return null
	}
}

PacketData& ScratchAck::InsertPacketData(uint16_t sequence)
{
	const int index = sequence % bufferSize;
	sequence_buffer[index] = sequence; //overwrite what ever is in the indexed slot 
	return packet_data[index];
}
