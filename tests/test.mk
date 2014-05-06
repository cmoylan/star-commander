TEST_DIR = tests
TEST_OBJS = tests/level_test.h tests/character_test.h
SRC_OBJS = src/Level.cpp src/Character.cpp

CFLAGS = -DTEST_MODE

TEST_INCLUDE_PATHS = -I./$(TEST_DIR)/cxxtest-4.3 -I./src

TESTGEN = ./$(TEST_DIR)/cxxtest-4.3/bin/cxxtestgen

TEST_RUNNER = ./$(TEST_DIR)/runner
TEST_RUNNER_SRC = $(TEST_RUNNER).cpp


test: test_compile
	$(TEST_RUNNER)

test_compile: test_parse
	$(CC) $(TEST_RUNNER_SRC) $(SRC_OBJS) $(INCLUDE_PATHS) \
	$(TEST_INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) \
	$(CFLAGS) -o $(TEST_RUNNER)

test_parse: test_clean
	$(TESTGEN) --runner=ParenPrinter \
	-o $(TEST_RUNNER_SRC) $(TEST_OBJS)

test_clean:
	rm -f $(TEST_RUNNER) $(TEST_RUNNER_SRC)
