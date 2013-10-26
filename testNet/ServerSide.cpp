//------------------------------------------------------------------------------
// Class: ServerSide
//------------------------------------------------------------------------------

#include "ServerSide.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Number.h"

namespace TestNet {

//==============================================================================
// ServerSide
//==============================================================================

IMPLEMENT_SUBCLASS(ServerSide, "ServerSide")
EMPTY_SLOTTABLE(ServerSide)
EMPTY_SERIALIZER(ServerSide)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
ServerSide::ServerSide()
{
    STANDARD_CONSTRUCTOR()

    loopCounter = 0;
}


//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ServerSide::copyData(const ServerSide& org, const bool)
{
   BaseClass::copyData(org);
   loopCounter = org.loopCounter;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void ServerSide::deleteData()
{
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void ServerSide::reset()
{
    BaseClass::reset();
    loopCounter = 0;
}

//------------------------------------------------------------------------------
// Send and receive test messages
//------------------------------------------------------------------------------
void ServerSide::updateData(const Eaagles::LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateData(dt);

    if (areNetworksEnabled()) {
        // Looking for a message from the client
        char buffer[MAX_SIZE+1];
        unsigned int n = recvData(buffer, MAX_SIZE);
        std::cout << "n = " << n << std::endl;
        if (n > 0) {
            buffer[n] = 0;
            std::cout << "RECV: " << buffer << std::endl;
            // And send it right back to the client
            Eaagles::lcSleep(1000);
            bool ok = sendData(buffer, n);
            if (ok) {
               std::cout << "SENT: " << buffer << std::endl << std::endl;

               // End check
               loopCounter++;
               if (getLoops() > 0 && loopCounter >= getLoops()) {
                   closeConnections();
                   std::cout << "Exit: " << getLoops() << " loops completed!" << std::endl;
                   exit(0);
               }

            }
        }
    }
}

} // End namespace
