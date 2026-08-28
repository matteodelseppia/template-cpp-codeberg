#include "Mi/Hello.hpp"

#include <ostream>

#include <doctest/doctest.h>

TEST_CASE("hello message") { CHECK(Mi::HelloMessage() == "Hello, world!"); }
