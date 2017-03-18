
#ifndef __oe_xzmq_factory_H__
#define __oe_xzmq_factory_H__

#include <string>

namespace oe {
namespace base { class Object; }
namespace xzmq {

base::Object* factory(const std::string& name);

}
}

#endif
