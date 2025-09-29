#pragma once
#include "Payload.h"
#include <vector>

#define SERIAL_EXPORTS

#ifdef SERIAL_EXPORTS
#define SERIAL_API __declspec(dllexport)
#else
#define SERIAL_API __declspec(dllimport)
#endif

extern "C" 
{
	//serialize the payload struct into one char array to send over the network
	SERIAL_API void SerializePayload(Payload payloadToSend, char* transmitBuf);

	//serialize the payload struct into one char array to send over the network
	SERIAL_API void SerializePayloadWithPointer(Payload* payloadToSend, char* transmitBuf);

	//deserialize an incoming char buffer to a valid payload struct
	SERIAL_API void DeserializePayload(char* recieveBuf, int size, Payload& payload);


	//when we need to convert a float to big endian for sending across the network
	SERIAL_API void SerializeFloat(float value, std::vector<char>& outputBuffer);

	SERIAL_API float DeserializeFloat(std::vector<char> payloadChanges, int startingPoint);

	SERIAL_API void SerializeInt32(int value, std::vector<char>& outputBuf);
	SERIAL_API int DeserializeInt32(std::vector<char> payload, int startingPoint);

	SERIAL_API void SerializeUnsignedInt16(uint16_t value, std::vector<char>& outputBuf);
	SERIAL_API uint16_t DeserializeUnsignedInt16(std::vector<char> payload, int startingPoint);

	SERIAL_API void SerializeUnsignedInt32(uint32_t value, std::vector<char>& outputBuf);
	SERIAL_API uint32_t DeserializeUnsignedInt32(std::vector<char> payload, int startingPoint);


}