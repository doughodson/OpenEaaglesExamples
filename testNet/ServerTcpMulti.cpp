
#include "ServerTcpMulti.h"

#include "openeaagles/basic/NetHandler.h"
#include "openeaagles/basic/Number.h"

namespace TestNet {

//==============================================================================
// ServerTcpMulti
//==============================================================================

IMPLEMENT_SUBCLASS(ServerTcpMulti,"ServerTcpMulti")
EMPTY_SLOTTABLE(ServerTcpMulti)
EMPTY_SERIALIZER(ServerTcpMulti)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
ServerTcpMulti::ServerTcpMulti()
{
    STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ServerTcpMulti::copyData(const ServerTcpMulti& org, const bool)
{
   BaseClass::copyData(org);
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void ServerTcpMulti::deleteData()
{
}

//------------------------------------------------------------------------------
// reset()
//------------------------------------------------------------------------------
void ServerTcpMulti::reset()
{
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// Send and receive test messages
//------------------------------------------------------------------------------
void ServerTcpMulti::updateData(const Eaagles::LCreal dt)
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

} // End namespace
