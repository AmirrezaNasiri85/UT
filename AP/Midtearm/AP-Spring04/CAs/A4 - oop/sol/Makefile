APP_NAME=utghalam
BINARY_NAME=UTGhalam

CC=g++
C_FLAGS=-std=c++20 -Wall -Wextra
RUN_ARGS=./csvs/questions.csv

OBJECTS_DIR=lib
SRC_DIR=src
DEPS=$(OBJECTS:.o=.d)

SRCS=$(shell find ${SRC_DIR} -type f \( -name "*.cpp" \))
HEADERS=$(shell find ${SRC_DIR} -type f \( -name "*.hpp" \))
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJECTS_DIR)/%.o, ${SRCS})

$(APP_NAME): $(OBJECTS) | format
	$(CC) $(C_FLAGS) $^ -o ${BINARY_NAME}

run: $(APP_NAME)
	./$(BINARY_NAME) $(RUN_ARGS)

$(OBJECTS): $(HEADERS) | $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(C_FLAGS) -c $< -o $@

$(OBJECTS_DIR):
	cp $(SRC_DIR) $(OBJECTS_DIR) -r
	find $(OBJECTS_DIR) -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec rm {} \;

-include $(DEPS)

clean:
	rm -rf lib ${BINARY_NAME}

format:
	find . -type f \( -name '*.cpp' -or -name '*.hpp' \) -exec clang-format -i {} +

test: $(APP_NAME)
	./judge.sh -t
