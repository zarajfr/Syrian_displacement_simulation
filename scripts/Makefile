CXX:=g++
LDFLAGS:= -c
all: myout

myout: main.o ga_destination.o node.o graph.o agent.o simulator.o
	g++ main.o node.o graph.o agent.o simulator.o ga_destination.o -pthread -O3 -o myout
main.o: main.cpp openga.hpp
	g++ -c -O3 -std=c++11 -pthread -Wall -Wconversion -Wfatal-errors -Wextra main.cpp
simulator.o: simulator.cpp
	g++ -c simulator.cpp
agent.o: agent.cpp
	g++ -c agent.cpp
graph.o: graph.cpp
	g++ -c graph.cpp
node.o: node.cpp
	g++ -c node.cpp
# example_mo1.o: example_mo1.cpp openga.hpp
# 	g++ -c -O3 -std=c++11 -pthread -Wall -Wconversion -Wfatal-errors -Wextra example_mo1.cpp
ga_destination.o: ga_destination.cpp openga.hpp
	g++ -c -O3 -std=c++11 -pthread -Wall -Wconversion -Wfatal-errors -Wextra ga_destination.cpp

PHONEY: clean

clean:
	rm -f *.o myout

# OTHER_FLAG:= -c
# DEBUG_FLAG:= -g -03
# RELESE_FLAG:= -O3 -s -DNDEBUG
# CURRENT_FLAGS:= $(RELESE_FLAG)
# CURRENT_FLAGS += -std=c++11 -pthread -I./src -Wall -Wconversion -Wfatal-errors -Wextra
# BIN=./bin
#
# LIBS:= #-lboost_system -lboost_thread -lboost_chrono
# G_LIBS:= -lGL -lGLU -lglut -lGLEW -lSDL -lSDL2main -lSDL2
#
# OBJS_1 := examples/mo-1/example_mo1.cpp
# OBJS_2 := examples/mo-1/main.cpp examples/mo-1/simulator.cpp examples/mo-1/agent.cpp examples/mo-1/graph.cpp examples/mo-1/node.cpp
# OBJS_3 := main.o node.o graph.o agent.o simulator.o
#
#
# all: ex_mo1
#
# ex_mo1:
# 	$(CXX) $(OTHER_FLAG) $(OBJS_2)
# 	$(CXX) $(CURRENT_FLAGS) $(OBJS_1)
# 	$(CXX) $(OBJS_3) -o $(BIN)/example_mo1 $(LIBS)
# 	@echo "-----------------------------------------------"
# 	$(BIN)/example_mo1
#
# clean:
# 	rm ./bin/example_*
