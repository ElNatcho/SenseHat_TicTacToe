

OBJS := *.o
SRCF := *.cpp *.hpp
CXX  := g++
CXX_flags := -std=c++11

main: $(OBJS)
	$(CXX) -o main $(OBJS)

$(OBJS): $(SRCF)
	$(CXX) $(CXX_flags) -c $(SRCF)
