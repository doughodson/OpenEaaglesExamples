//------------------------------------------------------------------------------
// Class: Endpoint
//------------------------------------------------------------------------------

#include "Endpoint.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/nethandlers/TcpHandler.h"
#include "openeaagles/basic/Number.h"

namespace Eaagles {
namespace Test {

//==============================================================================
// Endpoint
//==============================================================================

IMPLEMENT_SUBCLASS(Endpoint, "Endpoint")
EMPTY_SERIALIZER(Endpoint)

BEGIN_SLOTTABLE(Endpoint)
   "netHandler",           // 1) Network handler (input/output, or just output if netInput is defined)
   "netInput",             // 2) Optional input handler (otherwise 'netHandler' is used)
   "netOutput",            // 3) Alias for the 'netHandler' slot to be use when using the 'netInput' slot.
   "noWait",               // 4) No wait (unblocked) I/O flag (default: false -- blocked I/O)
   "loops",                // 5) Number of messages to send/recv before disconnecting and halting (default: infinite)
END_SLOTTABLE(Endpoint)

// Map slot table to handles 
BEGIN_SLOT_MAP(Endpoint)
    ON_SLOT(1, setSlotNetwork,   Eaagles::Basic::NetHandler)
    ON_SLOT(2, setSlotNetInput,  Eaagles::Basic::NetHandler)
    ON_SLOT(3, setSlotNetwork,   Eaagles::Basic::NetHandler)
    ON_SLOT(4, setSlotNoWait,    Eaagles::Basic::Number)
    ON_SLOT(5, setSlotLoops,     Eaagles::Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Endpoint::Endpoint() : netHandler(0), netInput(0) 
{
   STANDARD_CONSTRUCTOR()

   networkInitialized = false;
   networkInitFailed = false;
   noWaitFlag = false;
   loops = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Endpoint::copyData(const Endpoint& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      netHandler = 0;
      netInput = 0;
   }

   noWaitFlag = org.noWaitFlag;
   loops = org.loops;

   // We need to init this ourselves, so
   netHandler = 0;
   netInput = 0;
   networkInitialized = false;
   networkInitFailed = false;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Endpoint::deleteData()
{
   netHandler = 0;
   netInput = 0;
}

//------------------------------------------------------------------------------
// reset() -- Reset vehicle
//------------------------------------------------------------------------------
void Endpoint::reset()
{
   BaseClass::reset();

   // Initialize the networks
   if (!networkInitialized && !networkInitFailed) {
      networkInitialized = initNetworks();
      networkInitFailed = !networkInitialized;
   }
}

//------------------------------------------------------------------------------
// initNetworks() -- Init the networks
//------------------------------------------------------------------------------
bool Endpoint::initNetworks()
{
    // Init the main net handler
    bool ok1 = false; // (required)
    if (netHandler != 0) ok1 = netHandler->initNetwork(noWaitFlag);

    // Init the input net handler
    bool ok2 = true; // (optional)
    if (netInput != 0) ok2 = netInput->initNetwork(noWaitFlag);

    return (ok1 && ok2);
}

//------------------------------------------------------------------------------
// Send (transmit) our data buffer; returns true if successful.
// 'size' just be less than MAX_SIZE.
//------------------------------------------------------------------------------
bool Endpoint::sendData(const char* const msg, const unsigned int size)
{
   bool ok = false;
   if (msg != 0 && size > 0 && size < MAX_SIZE  && areNetworksEnabled()) {
      ok = netHandler->sendData(msg, size);
   }
   else {
      std::cerr << "NetTester::sendData(): unable to send data; ";
      if (msg == 0) std::cerr << "No message buffer.";
      if (size == 0 || size >= MAX_SIZE) std::cerr << "invalid message size.";
      if (!areNetworksEnabled()) std::cerr << "No network connection.";
      std::cerr << std::endl;
   }
   return ok;
}

//------------------------------------------------------------------------------
// Receive a data buffer; returns number of bytes received;
// 'maxsize' just be less than MAX_SIZE.
//------------------------------------------------------------------------------
unsigned int Endpoint::recvData(char* const msg, const unsigned int maxsize)
{
    int n = 0;
    if (msg != 0 && maxsize > 0 && maxsize <= MAX_SIZE && areNetworksEnabled()) {
        char buffer[MAX_SIZE];
        unsigned int n0 = 0;
        if (netInput != 0) {
            // use the optional 'netInput' handler
            n0 = netInput->recvData( buffer, MAX_SIZE );
        }
        else {
            // default: use the 'netHandler'
            n0 = netHandler->recvData( buffer, MAX_SIZE );
        }
        if (n0 > 0) {
            for (unsigned int i = 0; i < n0; i++) {
                msg[i] = buffer[i];
            }
            n = n0;
        }
    }
    else {
      std::cerr << "NetTester::recvData(): unable to receive data; ";
      if (msg == 0) std::cerr << "No message buffer.";
      if (maxsize == 0 || maxsize >= MAX_SIZE) std::cerr << "invalid max message size.";
      if (!areNetworksEnabled()) std::cerr << "No network connection.";
      std::cerr << std::endl;
    }
    return n;
}


//------------------------------------------------------------------------------
// Returns true if the networks are initialized and connected
//------------------------------------------------------------------------------
bool Endpoint::areNetworksEnabled() const
{
    bool ok = networkInitialized;
    if (ok && netHandler != 0) ok = netHandler->isConnected();
    if (ok && netInput != 0)   ok = netInput->isConnected();
    return ok;
}

//------------------------------------------------------------------------------
// close all network connections
//------------------------------------------------------------------------------
void Endpoint::closeConnections()
{
    if (netHandler != 0) netHandler->closeConnection();
    if (netInput != 0)   netInput->closeConnection();
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

// Network Handler
bool Endpoint::setSlotNetwork(Eaagles::Basic::NetHandler* const msg)
{
    netHandler = msg;
    return true;
}

// Input Handler
bool Endpoint::setSlotNetInput(Eaagles::Basic::NetHandler* const msg)
{
    netInput = msg;
    return true;
}

// No wait (unblocked) I/O flag
bool Endpoint::setSlotNoWait(Eaagles::Basic::Number* const msg)
{
    bool ok = false;
    if (msg != 0) {
        noWaitFlag = msg->getBoolean();
        ok = true;
    }
    return ok;
}

// Number of message loops
bool Endpoint::setSlotLoops(Eaagles::Basic::Number* const msg)
{
    bool ok = false;
    if (msg != 0) {
        int ia = msg->getInt();
        if (ia >= 0) {
            loops = static_cast<unsigned int>(ia);
            ok = true;
        }
    }
    return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Component
//------------------------------------------------------------------------------
Basic::Object* Endpoint::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}
}

