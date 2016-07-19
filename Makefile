CC = g++
RM = rm -rf

LD_FLAGS := 
CC_FLAGS := --std=c++11 -Werror -Wall

CPP_SRC := $(wildcard source/*.cpp)
OBJ_SRC := $(addprefix source/,$(notdir $(CPP_SRC:.cpp=.o)))

BUILD_MAIN = build_kdtree
QUERY_MAIN = query_kdtree

CPP_UNIT := $(wildcard tests/*.cpp)
OBJ_UNIT := $(addprefix tests/,$(notdir $(CPP_UNIT:.cpp=.o)))

BUILD_OBJ_MAIN := build_kdtree.main.o
QUERY_OBJ_MAIN := query_kdtree.main.o

GTEST_INC := -Itests -Isource
CC_FLAGS += $(GTEST_INC)

# let us assume that gtest library has been compiled and installed to /usr/lib or something
GTEST_LIB := -lgtest -lgtest_main -lpthread 

UNITTEST = kdtree.unit.t

all: $(BUILD_MAIN) $(QUERY_MAIN) 

$(BUILD_MAIN): $(OBJ_SRC) $(BUILD_OBJ_MAIN)
	$(CC) $(LD_FLAGS) -o $@ $^

$(QUERY_MAIN): $(OBJ_SRC) $(QUERY_OBJ_MAIN)
	$(CC) $(LD_FLAGS) -o $@ $^

test: $(OBJ_SRC) $(OBJ_UNIT)
	$(CC) $(LD_FLAGS) -o $(UNITTEST) $^ $(GTEST_LIB)

%.o: %.cpp %.h
	$(CC) $(CC_FLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

cleanmain:
	$(RM) $(OBJ_SRC) $(BUILD_OBJ_MAIN) $(QUERY_OBJ_MAIN) $(BUILD_MAIN) $(QUERY_MAIN)

cleantest:
	$(RM) $(BUILD_OBJ_MAIN) $(QUERY_OBJ_MAIN) $(OBJ_UNIT) $(UNITTEST)

cleanall: cleanmain cleantest

