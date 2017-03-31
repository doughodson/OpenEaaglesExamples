
#ifndef __factory_H__
#define __factory_H__

#include <string>

namespace oe {
namespace base { class Object; }
}

oe::base::Object* factory(const std::string& name);

#endif
