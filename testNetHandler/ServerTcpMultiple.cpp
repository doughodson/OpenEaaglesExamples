
#include "ServerTcpMultiple.hpp"

#include "openeaagles/base/Number.hpp"
#include <iostream>

using namespace oe;

IMPLEMENT_SUBCLASS(ServerTcpMultiple, "ServerTcpMultiple")
EMPTY_SLOTTABLE(ServerTcpMultiple)
EMPTY_SERIALIZER(ServerTcpMultiple)

ServerTcpMultiple::ServerTcpMultiple()
{
    STANDARD_CONSTRUCTOR()
}

void ServerTcpMultiple::copyData(const ServerTcpMultiple& org, const bool)
{
   BaseClass::copyData(org);
}

void ServerTcpMultiple::deleteData()
{
}

void ServerTcpMultiple::reset()
{
    BaseClass::reset();
}

// send and receive test messages
void ServerTcpMultiple::updateData(const double dt)
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
