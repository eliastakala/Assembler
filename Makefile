CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

hello: hello.cpp
	$(CXX) $(CXXFLAGS) hello.cpp -o hello

run: hello
	./hello

clean:
	rm -f hello