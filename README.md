# C++ Codeberg project template

A cross-platform C++20 starter with CMake presets, tests, formatting, static
analysis, and a GitHub Actions workflow that can publish its result to a
Codeberg mirror.

## Start a project

Create a repository from this template, then replace the sample identifiers:

| Template identifier | Replace with |
| --- | --- |
| `template_project` | Your lowercase CMake target/project name |
| `TemplateProject` | Your C++ namespace and include-directory name |
| `TEMPLATE_PROJECT` | Your uppercase CMake option prefix |

Rename `include/TemplateProject`, `TemplateProject.hpp`,
`src/TemplateProject.cpp`, and `tests/TemplateProjectTest.cpp` to match. Also
replace the `[year]` and `[copyright holder]` placeholders in `LICENSE` before
publishing. The sample library, executable, and test are deliberately small;
reshape or remove them for the kind of project you are building.

## Local development

Requirements: CMake 3.24+, Ninja, a C++20 compiler, clang-format, and
clang-tidy. Tests are fetched by CMake with `FetchContent`.

```sh
# Use the preset for your host: macos-debug, linux-debug, or windows-debug.
cmake --preset linux-debug
cmake --build --preset linux-debug
ctest --preset linux-debug

# Check formatting and static analysis as CI does.
clang-format --dry-run --Werror $(git ls-files '*.c' '*.cc' '*.cpp' '*.cxx' '*.h' '*.hh' '*.hpp' '*.hxx')
clang-tidy --warnings-as-errors='*' -p build/linux-debug $(git ls-files '*.c' '*.cc' '*.cpp' '*.cxx')
```

Release presets are available for all three platforms. Every preset writes its
build tree and `compile_commands.json` under `build/<preset>`.

Set `TEMPLATE_PROJECT_ENABLE_CLANG_TIDY=ON` at configure time to run
clang-tidy during each compilation instead of invoking it separately.

## CI and Codeberg status

`.github/workflows/CI.yml` builds, tests, checks formatting, and runs
clang-tidy on Linux, macOS, and Windows. It does not contain a repository name.

If GitHub Actions is used for a repository mirrored to Codeberg, add these in
the GitHub repository settings:

- **Variable** `CODEBERG_REPOSITORY`: the Codeberg `owner/repository` path.
- **Secret** `CODEBERG_TOKEN`: a Codeberg access token permitted to create
  commit statuses for that repository.

With the variable set, push builds publish `github-actions/ci` to the matching
Codeberg commit. The reporting job is skipped when the variable is absent, so a
project that does not use a Codeberg mirror needs no CI edits. Pull requests
are intentionally not reported because fork secrets and mirrored commit SHAs
are not reliable there.

## Tooling configuration

- `.clang-format` is the repository-wide LLVM-derived formatting policy.
- `.clang-tidy` enables the naming policy and treats diagnostics as errors.
- `CMakePresets.json` is the single entry point for reproducible local and CI
  builds. Put developer-specific overrides in `CMakeUserPresets.json` (ignored
  by Git).
