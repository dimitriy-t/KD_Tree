CC = g++
RM = rm -rf

LD_FLAGS := 
CC_FLAGS := --std=c++11 -Werror -Wall

CPP_SRC := $(wildcard source/*.cpp)
OBJ_SRC := $(addprefix source/,$(notdir $(CPP_SRC:.cpp=.o)))

MAIN = kdtree

CPP_UNIT := $(wildcard tests/*.cpp)
OBJ_UNIT := $(addprefix tests/,$(notdir $(CPP_UNIT:.cpp=.o)))

CPP_MAIN := main.cpp
OBJ_MAIN := main.o

GTEST_INC := -Itests -Isource
CC_FLAGS += $(GTEST_INC)

# let us assume that gtest library has been compiled and installed to /usr/lib or something
GTEST_LIB := -lgtest -lgtest_main -lpthread 

UNITTEST = kdtree.unit.t

all: $(MAIN)

$(MAIN): $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) $(LD_FLAGS) -o $@ $^

test: $(OBJ_SRC) $(OBJ_UNIT)
	$(CC) $(LD_FLAGS) -o $(UNITTEST) $^ $(GTEST_LIB)

%.o: %.cpp %.h
	$(CC) $(CC_FLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

cleanmain:
	$(RM) $(OBJ_SRC) $(OBJ_MAIN) $(MAIN)

cleantest:
	$(RM) $(OBJ_SRC) $(OBJ_UNIT) $(UNITTEST)

cleanall: cleanmain cleantest

