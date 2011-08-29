//------------------------------------------------------------------------------
// Class: ClientSide
//------------------------------------------------------------------------------
#ifndef __ClientSide_H_A30225AF_F15E_407b_95F8_27E8242756D4__
#define __ClientSide_H_A30225AF_F15E_407b_95F8_27E8242756D4__

#include "NetTester.h"

namespace TestNet {

//------------------------------------------------------------------------------
// Class:  ClientSide
// Base class:  Object-> Component-> NetTester -> ClientSide
//
// Description: Sends an ASCII test message to the server side and accepts the response message.
//
// Form name: ClientSide
//
// Guid: {A30225AF-F15E-407b-95F8-27E8242756D4}
//------------------------------------------------------------------------------
class ClientSide : public NetTester {
   DECLARE_SUBCLASS(ClientSide,NetTester)

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
