# Project Configuration
PROJECT_NAME = cerraria
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Iinc -Ideps/raylib/src -Ideps/imgui -Ideps/rlImGui
LDFLAGS = -lraylib -lpthread -ldl -lm

# Directories
SRC_DIR = src
BUILD_DIR = build
DEPS_DIR = deps

# Dependencies (raylib and imgui)
RAYLIB_GIT = https://github.com/raysan5/raylib.git
IMGUI_GIT = https://github.com/ocornut/imgui.git
RLIMGUI_GIT = https://github.com/raylib-extras/rlImGui.git

RAYLIB_DIR = $(DEPS_DIR)/raylib
IMGUI_DIR = $(DEPS_DIR)/imgui
RLIMGUI_DIR = $(DEPS_DIR)/rlImGui

RAYLIB_LIB = $(RAYLIB_DIR)/src/libraylib.a

# Gather Source Files
SOURCES = $(wildcard $(SRC_DIR)/**/*.cc) $(wildcard $(SRC_DIR)/*.cc)
IMGUI_SOURCES = $(IMGUI_DIR)/imgui.cpp \
                $(IMGUI_DIR)/imgui_demo.cpp \
                $(IMGUI_DIR)/imgui_draw.cpp \
                $(IMGUI_DIR)/imgui_tables.cpp \
                $(IMGUI_DIR)/imgui_widgets.cpp \
                $(RLIMGUI_DIR)/rlImGui.cpp

# Target
TARGET = $(BUILD_DIR)/$(PROJECT_NAME)

# Rules
.PHONY: all clean fetch_deps run

all: fetch_deps $(TARGET) run

$(TARGET): $(SOURCES) $(IMGUI_SOURCES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -L$(RAYLIB_DIR)/src

fetch_deps: fetch_raylib fetch_imgui fetch_rlimgui

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

fetch_imgui:
	@mkdir -p $(DEPS_DIR)
	@if [ ! -d $(IMGUI_DIR) ]; then \
		echo "Cloning ImGui..."; \
		git clone --depth 1 $(IMGUI_GIT) $(IMGUI_DIR); \
	fi

fetch_rlimgui:
	@mkdir -p $(DEPS_DIR)
	@if [ ! -d $(RLIMGUI_DIR) ]; then \
		echo "Cloning rlImGui..."; \
		git clone --depth 1 $(RLIMGUI_GIT) $(RLIMGUI_DIR); \
	fi

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
