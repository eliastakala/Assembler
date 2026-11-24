CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

hello: hello.cpp trim.cpp utils.h
	$(CXX) $(CXXFLAGS) hello.cpp trim.cpp -o hello

run: hello
	./hello

clean:
	rm -f hello