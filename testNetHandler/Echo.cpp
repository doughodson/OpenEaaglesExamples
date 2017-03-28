
#include "Echo.hpp"

#include "openeaagles/base/Number.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include <cstdlib>
#include <iostream>

using namespace oe;

IMPLEMENT_SUBCLASS(Echo, "Echo")
EMPTY_SLOTTABLE(Echo)
EMPTY_SERIALIZER(Echo)
EMPTY_DELETEDATA(Echo)

Echo::Echo()
{
    STANDARD_CONSTRUCTOR()
}

void Echo::copyData(const Echo& org, const bool)
{
    BaseClass::copyData(org);
    loopCounter = org.loopCounter;
}

void Echo::reset()
{
    BaseClass::reset();
    loopCounter = 0;
}

// send and receive test messages
void Echo::updateData(const double dt)
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
            base::msleep(1000);
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
