
#ifndef __oe_test_Factory_H__
#define __oe_test_Factory_H__

#include <string>

namespace oe {

namespace base { class Object; }

namespace test {

base::Object* factory(const std::string& name);

}
}

#endif

