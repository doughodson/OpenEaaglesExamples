
#ifndef __oe_xrecorder_factory_H__
#define __oe_xrecorder_factory_H__

#include <string>

namespace oe {
namespace base { class Object; }
namespace xrecorder {

base::Object* factory(const std::string& name);

}
}

#endif
