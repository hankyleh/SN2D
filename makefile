CXX := g++
SRC_DIR := src
BUILD_DIR := build
C_FLAGS := -O0 -std=c++17

SOURCES := input.cpp echo.cpp parse.cpp transport.cpp  msg.cpp main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
BUILD_OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS))

sn2d: $(BUILD_OBJECTS)
	$(CXX) $^ -o $@ $(C_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@  -I./src $(C_FLAGS)

clean:
	rm -rf $(BUILD_DIR) sn2d