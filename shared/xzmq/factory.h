
#ifndef __oe_xzmq_factory_H__
#define __oe_xzmq_factory_H__

namespace oe {

namespace base { class Object; }

namespace xzmq {

base::Object* factory(const char* name);

}
}

#endif
