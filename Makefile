# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Output executable
TARGET = game

# Source files 
SRCS = CppDemonLevel.cpp \
       Cutscene.cpp \
       Entity.cpp \
       Inventory.cpp \
       Item.cpp \
       ItemType.cpp \
       RussianDudeLevel.cpp \
       SaveLoad.cpp \
       Shotgun.cpp \
       VanillaMode.cpp \
       help.cpp \
       main.cpp \
       newstats.cpp 

# Header files 
HEADERS = CppDemonLevel.h \
          Cutscene.h \
          Entity.h \
          GameState.h \
          Inventory.h \
          Item.h \
          ItemType.h \
          RussianDudeLevel.h \
          SaveLoad.h \
          Shell.h \
          Shotgun.h \
          VanillaMode.h \
          help.h \
          main.h \
          newstats.h 

# Object files 
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation rule
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets 
.PHONY: all clean

run: $(EXEC)
	./$(EXEC)


.PHONY: all clean run
