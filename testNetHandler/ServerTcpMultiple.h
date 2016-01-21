//------------------------------------------------------------------------------
// Class: ServerTcpMultiple
//------------------------------------------------------------------------------
#ifndef __oe_test_ServerTcpMultiple_H__
#define __oe_test_ServerTcpMultiple_H__

#include "Endpoint.h"

namespace oe {
namespace test {

//------------------------------------------------------------------------------
// Class:  ServerTcpMultiple
//
// Description:
//
// Factory name: ServerTcpMulti
//
//------------------------------------------------------------------------------
class ServerTcpMultiple : public Endpoint
{
   DECLARE_SUBCLASS(ServerTcpMultiple, Endpoint)

public:
   ServerTcpMultiple();

   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

};

}
}

#endif
