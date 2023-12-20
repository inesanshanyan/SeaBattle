CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lncurses

SRCS = core.cpp main.cpp view.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = core.h view.h
EXEC = a.out

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC) core.h.gch view.h.gch
