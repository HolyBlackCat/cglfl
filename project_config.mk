# Sources
SOURCE_DIRS :=
SOURCES := cglfl.cpp

# Object directory
OBJECT_DIR := obj

# Resulting binary
OUTPUT_FILE := cglfl
LINKER_MODE := CXX

# Flags
CXXFLAGS := -Wall -Wextra -pedantic-errors -std=c++2a
LDFLAGS :=

# Build modes
$(call new_mode,debug)
$(mode_flags) CXXFLAGS += -g -D_GLIBCXX_ASSERTIONS

$(call new_mode,debug_hard)
$(mode_flags) CXXFLAGS += -g -D_GLIBCXX_DEBUG

$(call new_mode,release)
$(mode_flags) CXXFLAGS += -DNDEBUG -O3
