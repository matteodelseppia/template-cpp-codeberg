#include "TemplateProject/TemplateProject.hpp"

#include <ostream>

#include <doctest/doctest.h>

TEST_CASE("sample project name") {
  CHECK(TemplateProject::ProjectName() == "template_project");
}
