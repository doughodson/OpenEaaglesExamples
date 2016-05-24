//------------------------------------------------------------------------------
// Class: Sender
//------------------------------------------------------------------------------
#ifndef __oe_test_Sender_H__
#define __oe_test_Sender_H__

#include "Endpoint.h"

namespace oe {
namespace test {

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

    virtual void updateData(const double dt = 0.0) override;
    virtual void reset() override;

private:
    unsigned int msgCounter;    // test message counter
    bool         recvMode;      // True if in receive mode
};

}
}

#endif

