#ifndef GDCL_RS_H
#define GDCL_RS_H

#include <string>
#include <functional>

#include <gdcl/input.h>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace gdcl {
namespace script {

extern std::function<void()>			 func_init;
extern std::function<void()>			 func_kill;
extern std::function<void()>			 func_loop;
extern std::function<void(inpt::event)> func_input;

int load(const std::string& config_path);

const std::string execute(const std::string& script);

} // namespace script
} // namespace gdcl

#endif
