# Project Configuration
PROJECT_NAME = cerraria
CXX = g++
CXXFLAGS = -std=c++23 -Iinc -Ideps/raylib/src
LDFLAGS = -lraylib -lpthread -ldl

# Directories
SRC_DIR = src
BUILD_DIR = build
DEPS_DIR = deps

# Dependency (raylib)
RAYLIB_GIT = https://github.com/raysan5/raylib.git
RAYLIB_DIR = $(DEPS_DIR)/raylib
RAYLIB_LIB = $(RAYLIB_DIR)/src/libraylib.a

# Gather Source Files
SOURCES = $(wildcard $(SRC_DIR)/**/*.cc) $(wildcard $(SRC_DIR)/*.cc)

# Target
TARGET = $(BUILD_DIR)/$(PROJECT_NAME)

# Rules
.PHONY: all clean fetch_raylib

all: fetch_raylib $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -L$(RAYLIB_DIR)/src

fetch_raylib:
	@mkdir -p $(DEPS_DIR)
	@if [ ! -d $(RAYLIB_DIR) ]; then \
		echo "Cloning raylib..."; \
		git clone --depth 1 $(RAYLIB_GIT) $(RAYLIB_DIR); \
	fi
	@if [ ! -f $(RAYLIB_LIB) ]; then \
		echo "Building raylib..."; \
		cd $(RAYLIB_DIR)/src && make; \
	else \
		echo "Raylib is already built."; \
	fi

run: $(TARGET)
	./$(TARGET)
	
clean:
	rm -rf $(BUILD_DIR)
