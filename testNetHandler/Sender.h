//------------------------------------------------------------------------------
// Class: Sender
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Sender_H__
#define __Eaagles_Test_Sender_H__

#include "Endpoint.h"

namespace Eaagles {
namespace Test {

//------------------------------------------------------------------------------
// Class: Sender
//
// Description: Sends an ASCII test message to an endpoint and accepts the response message.
//
// Factory name: Sender
//------------------------------------------------------------------------------
class Sender : public Endpoint
{
    DECLARE_SUBCLASS(Sender, Endpoint)

public:
    Sender();

    void updateData(const LCreal dt = 0.0) override;
    void reset() override;

private:
    unsigned int msgCounter;    // test message counter
    bool         recvMode;      // True if in receive mode
};

}
}

#endif

