#pragma once
#include <iostream>

#define SACK_EXPORTS

#ifdef SACK_EXPORTS
#define SACK_API __declspec(dllexport)
#else
#define SACK_API __declspec(dllimport)
#endif

/// <summary>
/// the PacketData struct provides information of a packet's acked status
/// </summary>
struct PacketData 
{
	bool acked;
};

const int bufferSize = 1024;

class SACK_API ScratchAck 
{
	uint16_t mostRecentRecievedPacket;

	uint32_t sequence_buffer[bufferSize];

	PacketData packet_data[bufferSize];


	PacketData* GetPacketData(uint16_t providedSequence);
	PacketData& InsertPacketData(uint16_t sequence);
};