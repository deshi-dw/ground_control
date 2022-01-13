#ifndef GDCL_RS_H
#define GDCL_RS_H

#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace gdcl {
namespace rs {

struct rs {
    sol::state lua;

    rs();
    ~rs();

    const std::string run(const std::string& script);
};

} // namespace rs
} // namespace gdcl

#endif
