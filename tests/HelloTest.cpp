#include "Mi/Hello.hpp"

#include <doctest/doctest.h>

TEST_CASE("hello message") { CHECK(Mi::HelloMessage() == "Hello, world!"); }
