
#ifndef __oe_example_factory_H__
#define __oe_example_factory_H__

namespace oe {

namespace base { class Object; }

namespace example {

base::Object* factory(const char* name);

}
}

#endif
