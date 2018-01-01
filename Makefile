CXX_FLAGS=-I include
DEBUG_FLAGS=-DDEBUG

main: main.cpp
	g++ --std=c++11 $^ $(CXX_FLAGS) $(DEBUG_FLAGS) -o $@

clean:
	rm main
