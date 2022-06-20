#makefile
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

start:
	rm bin/*.*

serial:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize  -c -o src/pathfinder.o src/pathfinder.cpp
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o bin/pathfinder_serial.exe src/pathfinder.o -lm
	rm src/*.o

autovec:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS)  -c -o src/pathfinder.o src/pathfinder.cpp
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -o bin/pathfinder_autovec.exe src/pathfinder.o -lm
	rm src/*.o

explicitvec:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -fno-tree-vectorize -c -o src/pathfinder.o src/pathfinder.cpp ; \
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -fno-tree-vectorize -o bin/pathfinder_explicitvec.exe src/*.o -lm ; \
	rm src/*.o ;

fullvec:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -c -o src/pathfinder.o src/pathfinder.cpp ; \
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -o bin/pathfinder_explicitvec.exe src/*.o -lm ; \
	rm src/*.o ;

clean:
	rm bin/*.dump; \
	rm bin/*.exe;