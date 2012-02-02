TARGET = bin/lbm

CXXFLAGS = -Wall -pedantic
LDFLAGS = -Wall -pedantic

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,obj/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJS)
