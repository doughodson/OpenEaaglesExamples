
#ifndef __oe_test_Factory_H__
#define __oe_test_Factory_H__

namespace oe {

namespace base { class Object; }

namespace test {

base::Object* factory(const char* name);

}
}

#endif
