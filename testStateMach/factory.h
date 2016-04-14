
#ifndef __oe_test_factory_H__
#define __oe_test_factory_H__

#include <string>

namespace oe {

namespace base { class Object; }

namespace test {

base::Object* factory(const std::string& name);

}
}

#endif
