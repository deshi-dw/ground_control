#ifndef GDCL_RS_H
#define GDCL_RS_H

#include <string>
#include <stdexcept>

#include "gdcl/input.h"

namespace gdcl {
namespace script {

typedef std::runtime_error error;

int load(const std::string& config_path);
int close();

int init();
int kill();
int loop();
int input(inpt::dev& dev, inpt::event e);

const std::string execute(const std::string& script);

} // namespace script
} // namespace gdcl

#endif
