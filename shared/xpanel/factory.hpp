
#ifndef __oe_xpanel_factory_H__
#define __oe_xpanel_factory_H__

#include <string>

namespace oe {
namespace base { class Object; }
namespace xpanel {
base::Object* factory(const std::string& name);
}
}

#endif
