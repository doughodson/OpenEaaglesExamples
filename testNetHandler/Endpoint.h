//------------------------------------------------------------------------------
// Class: Endpoint
//------------------------------------------------------------------------------
#ifndef __oe_test_Endpoint_H__
#define __oe_test_Endpoint_H__

#include "openeaagles/basic/Component.h"

namespace oe {

namespace basic { class NetHandler; class Number; }

namespace test {

//------------------------------------------------------------------------------
// Class: Endpoint
//
// Description: Common basic class that contains network handlers
//
// Slots:
//      netHandler  <NetHandler>    Network handler (input/output, or just output if 'netInput' is defined)
//      netInput    <NetHandler>    Optional input handler (otherwise 'netHandler' is used)
//      netOutput   <NetHandler>    Alias for the 'netHandler' slot.
//      noWait      <Number>        No wait (unblocked) I/O flag (default: false -- blocked I/O)
//      loops       <Number>        Number of messages to send/recv before disconnecting and
//                                  halting (default: infinite)
//
//------------------------------------------------------------------------------
class Endpoint : public basic::Component
{
   DECLARE_SUBCLASS(Endpoint, basic::Component)

public:
    static const unsigned int MAX_SIZE = 1024;  // Max buffer size

public:
    Endpoint();

    bool areNetworksEnabled() const;

    // Initialize the networks
    virtual bool initNetworks();

    // Send (transmit) our data buffer; returns true if successful.
    // 'size' just be less than MAX_SIZE.
    virtual bool sendData(const char* const msg, const unsigned int size);

    // Receive a data buffer; returns number of bytes received;
    // 'maxsize' just be less than MAX_SIZE.
    virtual unsigned int recvData(char* const msg, const unsigned int maxsize);

    // Slot functions
    virtual bool setSlotNetwork(basic::NetHandler* const msg);
    virtual bool setSlotNetInput(basic::NetHandler* const msg);
    virtual bool setSlotNoWait(basic::Number* const msg);
    virtual bool setSlotLoops(basic::Number* const msg);

    void reset() override;

protected:
    void closeConnections();
    unsigned int getLoops() const { return loops; }

private:
    basic::safe_ptr<basic::NetHandler> netHandler; // Network handler (input/output, or just output if netInput is defined)
    basic::safe_ptr<basic::NetHandler> netInput;   // Optional input handler (otherwise 'netHandler' is used)
    unsigned int loops;                            // Number of transfer loops (zero if no limit)
    bool   networkInitialized;                     // Network has been initialized
    bool   networkInitFailed;                      // Network initialization has failed
    bool   noWaitFlag;                             // No wait (unblocked) I/O flag
};

}
}

#endif

