#pragma once
#include <iostream>
#include <zlib.h>

#define SPH_EXPORTS

#ifdef SPH_EXPORTS
#define SPH_API __declspec(dllexport)
#else
#define SPH_API __declspec(dllimport)
#endif

struct SPH_API ScratchPacketHeader
{
	uint16_t sequence; //the Number this packet is e.g. #55
	uint16_t ack; //the previous packet number acknowedleged from the last sender
	uint32_t ack_bits; //the previous 32 packets recieved & acked from the last sender

	//we use CRC to prevent packets from being accepted if they were tampered with or corrupted on the journey
	uint32_t crc;

	ScratchPacketHeader() : crc(0), sequence(0), ack(0), ack_bits(0){}

	ScratchPacketHeader(uint16_t providedSequence, uint16_t providedAck, uint32_t providedAckBits, uint32_t providedCRC) : crc(0), sequence(0), ack(0), ack_bits(0)
	{
		sequence = providedSequence;
		ack = providedAck;
		ack_bits = providedAckBits;

		crc = providedCRC;
	}

};

extern "C"
{
	SPH_API void GenerateCRC(ScratchPacketHeader& OUTHeader, void* buf, size_t size);

	SPH_API ScratchPacketHeader* InitEmptyPacketHeader();

	SPH_API ScratchPacketHeader* InitPacketHeader(uint16_t providedSequence, uint16_t providedAck, uint32_t providedAckBits, uint32_t providedCRC);
}