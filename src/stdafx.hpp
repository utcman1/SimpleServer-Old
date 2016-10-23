#ifdef _WIN32
#pragma once
#endif

#pragma warning(push,1)
#pragma warning(disable : 4548) // expression before comma has no effect; expected expression with side-effect
#include <assert.h>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>



#include <boost/asio.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#pragma warning(pop)



#pragma warning(disable : 4503) // decorated name length exceeded, name was truncated
#pragma warning(disable : 4514) // unused inline function
#pragma warning(disable : 4710) // function not inlined
#pragma warning(disable : 4714) // function marked as __forceinline not inlined : boost::log
#pragma warning(disable : 4820) // bytes padding added
