#pragma once

#pragma warning(push,1)
#pragma warning(disable : 4548)
#include <assert.h>
#include <algorithm>
#include <cstdio>
#include <chrono>
#include <iostream>



#include <boost/asio.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/log/trivial.hpp>
#pragma warning(pop)



#pragma warning(disable : 4514) // unused inline function
#pragma warning(disable : 4710) // function not inlined
#pragma warning(disable : 4714) // function marked as __forceinline not inlined : boost::log
#pragma warning(disable : 4820) // bytes padding added
