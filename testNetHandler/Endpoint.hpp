
#ifndef __Endpoint_H__
#define __Endpoint_H__

#include "openeaagles/base/Component.hpp"

namespace oe {
namespace base { class NetHandler; class Number; }
}

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
class Endpoint : public oe::base::Component
{
   DECLARE_SUBCLASS(Endpoint, oe::base::Component)

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
    virtual bool setSlotNetwork(oe::base::NetHandler* const msg);
    virtual bool setSlotNetInput(oe::base::NetHandler* const msg);
    virtual bool setSlotNoWait(oe::base::Number* const msg);
    virtual bool setSlotLoops(oe::base::Number* const msg);

    virtual void reset() override;

protected:
    void closeConnections();
    unsigned int getLoops() const { return loops; }

private:
    oe::base::safe_ptr<oe::base::NetHandler> netHandler; // Network handler (input/output, or just output if netInput is defined)
    oe::base::safe_ptr<oe::base::NetHandler> netInput;   // Optional input handler (otherwise 'netHandler' is used)
    unsigned int loops {};                               // Number of transfer loops (zero if no limit)
    bool networkInitialized {};                          // Network has been initialized
    bool networkInitFailed {};                           // Network initialization has failed
    bool noWaitFlag {};                                  // No wait (unblocked) I/O flag
};

#endif
