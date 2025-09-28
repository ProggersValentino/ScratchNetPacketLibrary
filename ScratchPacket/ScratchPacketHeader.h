#pragma once
#include <iostream>

#define SPH_EXPORTS

#ifdef SPH_EXPORTS
#define SPH_API __declspec(dllexport)
#else
#define SPH_API __declspec(dllimport)
#endif

struct SPH_API ScratchPacketHeader
{
	uint16_t sequence;
	uint16_t ack;
	uint32_t ack_bits;

	uint32_t crc;

};