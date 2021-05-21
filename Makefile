# Building GoogleTest and running exercise-gtest unit tests against
# This Makefile is based on the sample Makefile provided in the 
# official GoogleTest GitHub Repo v1.7

# REMOVED FOR REQUIRED ENV in CI 
#export GTEST_DIR = /usr/local/src/googletest/googletest

# Flags passed to the preprocessor and compiler
CPPFLAGS += --coverage -std=c++11 -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.
TESTS = VideoListTest

# All Google Test headers. Adjust only if you moved the subdirectory
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.gcov *.gcda *.gcno *.gch

test:
	./VideoListTest 
	gcov -fbc vlist.cpp

# Builds gtest.a and gtest_main.a.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc
	    
gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc
	    
gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^
	
gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds the VideoList class and associated VideoListTes


vlist.o: vlist.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c vlist.cpp
	
VideoListTest.o : VideoListTest.cpp \
                     vlist.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c VideoListTest.cpp

VideoListTest : vlist.o  VideoListTest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

