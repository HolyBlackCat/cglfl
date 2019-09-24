# A helper function to run commands in shell.
# Same as `$(shell ...)`, but triggers an error on failure.
ifeq ($(filter --trace,$(MAKEFLAGS)),)
override safe_shell = $(shell $1)$(if $(filter-out 0,$(.SHELLSTATUS)),$(error Unable to execute `$1`, status $(.SHELLSTATUS)))
else
override safe_shell = $(info Shell command: $1)$(shell $1)$(if $(filter-out 0,$(.SHELLSTATUS)),$(error Unable to execute `$1`, status $(.SHELLSTATUS)))
endif

# Same as `safe_shell`, but discards the output and expands to a single space.
override safe_shell_exec = $(call,$(call safe_shell,$1))

# Some helper variables
override space = $(strip) $(strip)
override comma = ,


# Detect host OS
ifeq ($(OS),Windows_NT)
HOST_OS := windows
else
HOST_OS := linux
endif

ifeq ($(HOST_OS),windows)
override ext_exe := .exe
else
override ext_exe :=
endif


# Detect host shell
ifeq ($(call safe_shell,echo "foo"),"foo")
HOST_SHELL := windows
else
HOST_SHELL := linux
endif

ifeq ($(HOST_SHELL),windows)
override echo = echo $(subst <,^<,$(subst >,^>,$1))
else
override echo = echo '$1'
endif



# Executable name
OUTPUT := cglfl_generate$(ext_exe)

# Flags
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic-errors -g
LDFLAGS :=

# Targets
.PHONY: build
build: $(OUTPUT)

.PHONY: run
run: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): cglfl_generate.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	git clean -X -d -f


.PHONY: commands
commands:
ifneq ($(and $(filter windows,$(HOST_OS)),$(filter linux,$(HOST_SHELL))),)
# If we're on windows and use linux-style shell, we need to fix the path. `/c/foo/bar` -> `c:/foo/bar`
	$(eval override current_dir := $(subst <, ,$(subst $(space),/,$(strip $(join $(subst /, ,$(subst $(space),<,$(CURDIR))),:)))))
else
	$(eval override current_dir := $(CURDIR))
endif
	$(eval override output := compile_commands.json)
	$(eval override generated_dir := $(wildcard include/cglfl_*))
	$(call safe_shell_exec,$(call echo,[) >$(output))
	$(call safe_shell_exec,$(call echo,{"directory": "$(current_dir)"$(comma) "file": "$(current_dir)/cglfl_generate.cpp"$(comma) "command": "$(CXX) $(CXXFLAGS) cglfl_generate.cpp"}$(comma)) >>$(output))
	$(if $(filter-out 1,$(words $(generated_dir))),\
		$(if $(filter-out 0,$(words $(generated_dir))),\
			$(info Found generated code for *several* GL versions.),\
			$(info No generated code found.))\
		$(info Because of that, I can only generate commands for the code generator, but not for the loader.)\
	,\
		$(eval override files := $(wildcard src/*.cpp include/cglfl/*.hpp $(generated_dir)/cglfl_generated/*.hpp))\
    	$(foreach x,$(files),$(\
    		$(call safe_shell_exec,$(call echo,{"directory": "$(current_dir)"$(comma) "file": "$(current_dir)/$x"$(comma) "command": "$(CXX) $(CXXFLAGS) -Iinclude -I$(generated_dir) $x"}$(comma)) >>$(output))\
    	))\
	)
	$(call safe_shell_exec,$(call echo,]) >>$(output))
	@$(call echo,Done.)
