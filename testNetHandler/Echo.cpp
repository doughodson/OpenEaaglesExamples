//------------------------------------------------------------------------------
// Class: Echo
//------------------------------------------------------------------------------

#include "Echo.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Number.h"

#include <cstdlib>

namespace Eaagles {
namespace Test {

//==============================================================================
// Echo
//==============================================================================

IMPLEMENT_SUBCLASS(Echo, "Echo")
EMPTY_SLOTTABLE(Echo)
EMPTY_SERIALIZER(Echo)
EMPTY_DELETEDATA(Echo)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Echo::Echo()
{
    STANDARD_CONSTRUCTOR()

    loopCounter = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Echo::copyData(const Echo& org, const bool)
{
    BaseClass::copyData(org);
    loopCounter = org.loopCounter;
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void Echo::reset()
{
    BaseClass::reset();
    loopCounter = 0;
}

//------------------------------------------------------------------------------
// Send and receive test messages
//------------------------------------------------------------------------------
void Echo::updateData(const Eaagles::LCreal dt)
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
                   std::exit(0);
               }

            }
        }
    }
}

}
}

