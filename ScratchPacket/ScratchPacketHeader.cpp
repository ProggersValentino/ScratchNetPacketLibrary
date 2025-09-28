#include "pch.h"
#include "ScratchPacketHeader.h"

void GenerateCRC(ScratchPacketHeader& OUTHeader, void* buf, size_t size)
{
	OUTHeader.crc = crc32(0, Z_NULL, 0); //init

	OUTHeader.crc = crc32(OUTHeader.crc, reinterpret_cast<Bytef*>(buf), size);
}

ScratchPacketHeader* InitEmptyPacketHeader()
{
	return new ScratchPacketHeader();
}
