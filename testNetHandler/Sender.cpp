
#include "Sender.hpp"

#include "openeaagles/base/Number.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace oe;

IMPLEMENT_SUBCLASS(Sender, "Sender")
EMPTY_SLOTTABLE(Sender)
EMPTY_SERIALIZER(Sender)
EMPTY_DELETEDATA(Sender)

Sender::Sender()
{
    STANDARD_CONSTRUCTOR()
}

void Sender::copyData(const Sender& org, const bool)
{
    BaseClass::copyData(org);

    msgCounter = org.msgCounter;
    recvMode = org.recvMode;
}

void Sender::reset()
{
    BaseClass::reset();

    msgCounter = 0;
    recvMode = false;
}

// send and receive test messages
void Sender::updateData(const double dt)
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
            const auto n = static_cast<unsigned int>(std::strlen(buffer));
            base::msleep(1000);
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
            std::exit(0);
        }
    }
}
