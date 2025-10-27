CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2
INCLUDES = -Iinclude

BUILDDIR = build
TARGET = $(BUILDDIR)/graph_test

SOURCES = main.cpp
OBJECTS = $(BUILDDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(BUILDDIR)/main.o: main.cpp src/adjacency_list/undirected_unweighted.cpp include/adjacency_list.hpp include/graph.hpp include/types.hpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all run clean