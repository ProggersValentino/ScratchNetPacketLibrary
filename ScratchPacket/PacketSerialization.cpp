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

void SerializeInt32(int value, std::vector<char>& outputBuf)
{
	union {
		int originalValue;
		uint32_t convertedValue;
	};

	originalValue = value;

	//convert to big endian
	uint32_t networkedBigEndianInt = htonl(convertedValue);

	auto* byteConversion = reinterpret_cast<char*>(networkedBigEndianInt);

	outputBuf.insert(outputBuf.end(), byteConversion, byteConversion + sizeof(uint32_t));
}

int DeserializeInt32(std::vector<char> payload, int startingPoint)
{
	uint32_t convertedValue;

	memcpy(&convertedValue, &payload[startingPoint], sizeof(uint32_t));

	uint32_t smallEndian = ntohl(convertedValue);

	int deserializedInt = std::bit_cast<int>(smallEndian);

	return deserializedInt;
}

void SerializeUnsignedInt16(uint16_t value, std::vector<char>& outputBuf)
{
	
	uint16_t unconvertedValue = value;

	//convert to big endian to align with the network 
	uint16_t networkedBigEndianInt = htonl(unconvertedValue);

	//translate it to individual bytes
	auto* byteConversion = reinterpret_cast<char*>(networkedBigEndianInt);

	outputBuf.insert(outputBuf.end(), byteConversion, byteConversion + sizeof(uint16_t));
}

uint16_t DeserializeUnsignedInt16(std::vector<char> payload, int startingPoint)
{
	uint16_t convertedValue;

	memcpy(&convertedValue, &payload[startingPoint], sizeof(uint16_t));

	uint16_t smallEndian = ntohl(convertedValue);

	return smallEndian;
}

void SerializeUnsignedInt32(uint32_t value, std::vector<char>& outputBuf)
{
	uint32_t unconvertedValue = value;

	//convert to big endian to align with the network 
	uint32_t networkedBigEndianInt = htonl(unconvertedValue);

	//translate it to individual bytes
	auto* byteConversion = reinterpret_cast<char*>(networkedBigEndianInt);

	outputBuf.insert(outputBuf.end(), byteConversion, byteConversion + sizeof(uint32_t));
}

uint32_t DeserializeUnsignedInt32(std::vector<char> payload, int startingPoint)
{
	uint32_t convertedValue;

	memcpy(&convertedValue, &payload[startingPoint], sizeof(uint16_t));

	uint32_t smallEndian = ntohl(convertedValue);

	return smallEndian;
}
