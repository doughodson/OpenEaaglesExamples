//------------------------------------------------------------------------------
// Class: ClientSide
//------------------------------------------------------------------------------

#include "Sender.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Number.h"

#include <cstdio>

// disable all deprecation warnings for now, until we fix
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {

//==============================================================================
// Sender
//==============================================================================

IMPLEMENT_SUBCLASS(Sender, "Sender")
EMPTY_SLOTTABLE(Sender)
EMPTY_SERIALIZER(Sender)
EMPTY_DELETEDATA(Sender)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Sender::Sender()
{
    STANDARD_CONSTRUCTOR()

    msgCounter = 0;
    recvMode = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Sender::copyData(const Sender& org, const bool)
{
    BaseClass::copyData(org);

    msgCounter = org.msgCounter;
    recvMode = org.recvMode;
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void Sender::reset()
{
    BaseClass::reset();

    msgCounter = 0;
    recvMode = false;
}

//------------------------------------------------------------------------------
// Send and receive test messages
//------------------------------------------------------------------------------
void Sender::updateData(const Eaagles::LCreal dt)
{
    // Update base classes stuff
    BaseClass::updateData(dt);

    if (areNetworksEnabled()) {

        // Looking for reply from the server
        if (recvMode) {
            char buffer[MAX_SIZE+1];
            unsigned int n = recvData(buffer, MAX_SIZE);
            std::cout << "n = " << n << std::endl;
            if (n > 0) {
                buffer[n] = 0;
                std::cout << "RECV: " << buffer << std::endl << std::endl;
                recvMode = false;
           }
        }

        // Sending a message to the server
        else {
            char buffer[MAX_SIZE];
            sprintf(buffer, "Message(%d)", ++msgCounter);
            unsigned int n = (unsigned int)strlen(buffer);
            Eaagles::lcSleep(1000);
            bool ok = sendData(buffer, n);
            if (ok) {
                std::cout << "SENT: " << buffer << std::endl;
                recvMode = true;
            }
        }

        // End check
        if (!recvMode && getLoops() > 0 && msgCounter >= getLoops()) {
            closeConnections();
            std::cout << "Exit: " << getLoops() << " loops completed!" << std::endl;
            exit(0);
        }
    }
}

}
}

