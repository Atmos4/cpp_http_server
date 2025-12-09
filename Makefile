# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./src

# Link flags
LDFLAGS = -levent -levent_core -levent_extra -levent_pthreads

# Directories
SRC_DIR := src
BUILD_DIR := build

# Automatically find all .cpp files in SRC_DIR
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Convert .cpp → .o in BUILD_DIR
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET := server

# Default rule
all: $(BUILD_DIR) $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile each .cpp into build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
