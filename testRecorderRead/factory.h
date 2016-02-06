
#ifndef __oe_test_factory_H__
#define __oe_test_factory_H__

namespace oe {

namespace basic { class Object; }

namespace test {

basic::Object* factory(const char* name);

}
}

#endif
