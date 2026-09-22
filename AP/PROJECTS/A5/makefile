CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g -Isrc

TARGET = ./UTGame

OBJ_DIR = output

SRCS = src/main.cpp \
       src/Objects/Report.cpp \
       src/Objects/Match.cpp \
       src/Objects/Invitation.cpp \
       src/Objects/People.cpp \
       src/Management/GetManagement.cpp \
       src/Management/IOhandeling.cpp \
       src/Management/DataBase.cpp \
       src/Management/PostManagement.cpp \
       src/Management/SystemManager.cpp \
       src/Management/Delete.cpp \
       src/Management/PutManagement.cpp \
       src/Management/Error.cpp

OBJS = $(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
