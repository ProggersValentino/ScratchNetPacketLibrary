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
