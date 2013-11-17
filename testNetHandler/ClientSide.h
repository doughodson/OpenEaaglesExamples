//------------------------------------------------------------------------------
// Class: ClientSide
//------------------------------------------------------------------------------
#ifndef __Test_ClientSide_H__
#define __Test_ClientSide_H__

#include "Endpoint.h"

namespace Test {

//------------------------------------------------------------------------------
// Class: ClientSide
//
// Description: Sends an ASCII test message to the server side and accepts the response message.
//
// Form name: ClientSide
//------------------------------------------------------------------------------
class ClientSide : public Endpoint
{
    DECLARE_SUBCLASS(ClientSide, Endpoint)

public:
    ClientSide();

    // Component interface
    virtual void updateData(const Eaagles::LCreal dt = 0.0f);
    virtual void reset();

private:
    unsigned int msgCounter;    // test message counter
    bool         recvMode;      // True if in receive mode
};

}

#endif

