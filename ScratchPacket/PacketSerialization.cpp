#include "pch.h"
#include "PacketSerialization.h"
#include <bit>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib") //needed to use the byte conversion util functions


SERIAL_API void SerializePayload(Payload payloadToSend, char* transmitBuf)
{

	transmitBuf[0] = payloadToSend.bitMask;

	//copy over the vector data and put it in the transmit buffer starting at 2nd position
	memcpy(&transmitBuf[1], payloadToSend.setChanges.data(), payloadToSend.setChanges.size()); 
	//make sure if trying to copy over a vector you do a .data() to point to the data to send & .size() to determine how much other YOU WILL GET UNDEFINED BEHAVIOUR 
}

void SerializePayloadWithPointer(Payload* payloadToSend, char* transmitBuf)
{

}

SERIAL_API void DeserializePayload(char* recieveBuf, int size, Payload& payload)
{
	payload.bitMask = recieveBuf[0];

	int len = size - 1;

	payload.setChanges.resize(len);
	memcpy(payload.setChanges.data(), &recieveBuf[1], len);
}

SERIAL_API void SerializeFloat(float value, std::vector<char>& outputBuffer)
{
	union {
		float inputValue;
		uint32_t convertedValue;
	};

	inputValue = value;

	/*uint32_t convertedValue {std::bit_cast<uint32_t>(value)};*/

	uint32_t networkedBigEdian = htonl(convertedValue); //converted to big endian

	auto* byteConversion = reinterpret_cast<char*>(&networkedBigEdian);

	outputBuffer.insert(outputBuffer.end(), byteConversion, byteConversion + sizeof(uint32_t)); //inserting the convertted value at the end of the buffer 

}

float DeserializeFloat(std::vector<char> payloadChanges, int startingPoint)
{
	//char isolatedValue[4];
	uint32_t convertedValue;

	memcpy(&convertedValue, &payloadChanges[startingPoint], sizeof(uint32_t)); //we copy from the payloads array at a given point to a char[] to isolate the float

	uint32_t smallEndian = ntohl(convertedValue);

	//uint32_t convertedValue = reinterpret_cast<uint32_t>(isolatedValue);

	float deserializedFloat = std::bit_cast<float>(smallEndian);

	return deserializedFloat;
}
