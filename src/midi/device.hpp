#pragma once

#include "devices/base.hpp"

#if defined(__linux__)

#include "devices/oss.hpp"
#include "devices/alsa.hpp"

#elif defined(_WIN32) || defined(_WIN64)

#include "devices/wmm.hpp"

#endif