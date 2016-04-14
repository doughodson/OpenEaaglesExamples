
#ifndef __oe_example_factory_H__
#define __oe_example_factory_H__

#include <string>

namespace oe {

namespace base { class Object; }

namespace example {

base::Object* factory(const std::string& name);

}
}

#endif
