#include "pch.h"
#include "Payload.h"

PLOAD_API Payload* CreateEmptyPayload()
{
    return new Payload();
}

PLOAD_API Payload* CreatePayload(std::vector<EVariablesToChange> masks, std::vector<char> changedValues)
{
    Payload* payload = new Payload(masks, changedValues);

    return payload;
}

PLOAD_API Payload* CreatePayloadWithHeader(ScratchPacketHeader& headerToAssign, std::vector<EVariablesToChange> variablesMasks, std::vector<char>& changedValues)
{
    Payload* payloadToInit = new Payload(headerToAssign, variablesMasks, changedValues);
    return payloadToInit;
}
