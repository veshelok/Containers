CC               = g++
STANDART         = --std=c++17
DEBUG            = -g
SUPPRESS_WARN    = -Wno-type-limits
CFLAGS           = -Wall -Werror -Wextra -Weffc++ $(DEBUG) $(SUPPRESS_WARN)
OUT              = -o
RM               = rm -rf

HEADERS          = binary_search_tree.h \
                   s21_array.h \
                   s21_list.h \
                   s21_map.h \
                   s21_multiset.h \
                   s21_queue.h \
                   s21_set.h \
                   s21_stack.h \
                   s21_vector.h \
# TESTING PART
TEST_DIR         = test_sources
VPATH            = $(TEST_DIR)
TEST_SRCS        = array_test.cc \
                   binary_search_tree_test.cc \
                   list_test.cc \
                   map_test.cc \
                   multiset_test.cc \
                   queue_test.cc \
                   set_test.cc \
                   stack_test.cc \
                   test.cc \
                   vector_test.cc
TEST_OBJS        = $(TEST_SRCS:.cc=.o)
SEARCH_DIR       = -I.
GTEST_FLAGS      = $(STANDART) $(CFLAGS) -lgtest $(SEARCH_DIR)
ifeq ($(shell uname), Linux)
	GTEST_FLAGS      += -lpthread
endif

all: test

array_test.o: array_test.cc s21_array.h
	$(CC) -c $(GTEST_FLAGS) $<
binary_search_tree_test.o: binary_search_tree_test.cc binary_search_tree.h
	$(CC) -c $(GTEST_FLAGS) $<
list_test.o: list_test.cc s21_list.h
	$(CC) -c $(GTEST_FLAGS) $<
map_test.o: map_test.cc s21_map.h binary_search_tree.h
	$(CC) -c $(GTEST_FLAGS) $<
multiset_test.o: multiset_test.cc s21_multiset.h binary_search_tree.h
	$(CC) -c $(GTEST_FLAGS) $<
queue_test.o: queue_test.cc s21_queue.h
	$(CC) -c $(GTEST_FLAGS) $<
set_test.o: set_test.cc s21_set.h binary_search_tree.h
	$(CC) -c $(GTEST_FLAGS) $<
stack_test.o: stack_test.cc s21_stack.h
	$(CC) -c $(GTEST_FLAGS) $<
test.o: test.cc
	$(CC) -c $(GTEST_FLAGS) $<
vector_test.o: vector_test.cc s21_vector.h
	$(CC) -c $(GTEST_FLAGS) $<

TEST_OUT = test.out
$(TEST_OUT) : $(TEST_OBJS)
	$(CC) $^ $(GTEST_FLAGS) $(OUT) $@

test: $(TEST_OUT)
	./$(TEST_OUT)

GCOV_COMPILE_FLAGS  = -fprofile-arcs -ftest-coverage
GCOV_RESULT = *.gcda *.gcno *.gcov
GCOV_OUT    = gcov_report.out
GCOV        = gcov
GCOV_FLAGS  = -kjr

$(GCOV_OUT) : $(TEST_SRCS)
	$(RM) $(GCOV_RESULT)
	$(CC) $^ $(GTEST_FLAGS) $(GCOV_COMPILE_FLAGS) $(OUT) $@

gcov_report: $(GCOV_OUT)
	./$(GCOV_OUT)
	$(GCOV) $(GCOV_FLAGS) $(TEST_SRCS)

LCOV          = lcov
LCOV_FLAGS    = --no-external -c -d .
COVERAGE_INFO = coverage.info

$(COVERAGE_INFO): $(GCOV_OUT)
	./$(GCOV_OUT)
	$(LCOV) $(LCOV_FLAGS) $(OUT) $(COVERAGE_INFO)

LCOV_REPORT_DIR = lcov_report_dir
GENHTML         = genhtml

$(LCOV_REPORT_DIR) : $(COVERAGE_INFO)
	$(GENHTML) $^ $(OUT) $(LCOV_REPORT_DIR)

lcov_report: $(LCOV_REPORT_DIR)

.PHONY: linter clean

.INGORE: linter
linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cc *.h $(TEST_DIR)/*.cc
	$(RM) CPPLINT.cfg

clean:
	$(RM) $(TEST_OUT) $(TEST_OBJS) $(GCOV_RESULT) $(COVERAGE_INFO) \
	$(LCOV_REPORT_DIR) $(GCOV_OUT)

SUPPRESSING = --suppress=unusedFunction --suppress=missingIncludeSystem \
			  --suppress=unmatchedSuppression --suppress=missingInclude
.PHONY: cppcheck
cppcheck: $(TEST_SRCS)
	cppcheck --enable=all --language=c++ $(SUPPRESSING) $(STANDART) $^ $(HEADERS)

.PHONY: leaks valgrind
leaks: $(TEST_OUT)
	leaks --atExit -- ./$^

valgrind: $(TEST_OUT)
	valgrind -s ./$^
