//------------------------------------------------------------------------------
// Class: ServerTcpMultiple
//------------------------------------------------------------------------------

#include "ServerTcpMultiple.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Number.h"

namespace Eaagles {
namespace Test {

//==============================================================================
// ServerTcpMultiple
//==============================================================================

IMPLEMENT_SUBCLASS(ServerTcpMultiple, "ServerTcpMultiple")
EMPTY_SLOTTABLE(ServerTcpMultiple)
EMPTY_SERIALIZER(ServerTcpMultiple)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
ServerTcpMultiple::ServerTcpMultiple()
{
    STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ServerTcpMultiple::copyData(const ServerTcpMultiple& org, const bool)
{
   BaseClass::copyData(org);
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void ServerTcpMultiple::deleteData()
{
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void ServerTcpMultiple::reset()
{
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// Send and receive test messages
//------------------------------------------------------------------------------
void ServerTcpMultiple::updateData(const Eaagles::LCreal dt)
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
            bool ok = sendData(buffer, n);
            if (ok) {
               std::cout << "SENT: " << buffer << std::endl << std::endl;
            }
        }
    }
}

}
}
