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
	$(CXX) $(CXXFLAGS)  -fno-tree-vectorize  -c  -o src/pathfinder.o src/pathfinder.cpp $(BENCHMARKFLAGS) $(MEMORYFLAGS)
	$(CXX) $(CXXFLAGS)  -fno-tree-vectorize  -o bin/pathfinder_serial.exe src/pathfinder.o -lm $(BENCHMARKFLAGS) $(MEMORYFLAGS)
	rm src/*.o

autovec:
	$(CXX) $(CXXFLAGS)   -c -o src/pathfinder.o src/pathfinder.cpp $(BENCHMARKFLAGS) $(MEMORYFLAGS)
	$(CXX) $(CXXFLAGS)  -o bin/pathfinder_autovec.exe src/pathfinder.o -lm $(BENCHMARKFLAGS)  $(MEMORYFLAGS)
	rm src/*.o

explicitvec:
	$(CXX) $(CXXFLAGS)  $(VECTORFLAGS) -fno-tree-vectorize -c -o src/pathfinder.o src/pathfinder.cpp $(BENCHMARKFLAGS) $(MEMORYFLAGS) ; \
	$(CXX) $(CXXFLAGS)  $(VECTORFLAGS) -fno-tree-vectorize -o bin/pathfinder_explicitvec.exe src/*.o -lm $(BENCHMARKFLAGS)  $(MEMORYFLAGS); \
	rm src/*.o ;

fullvec:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -c -o src/pathfinder.o src/pathfinder.cpp $(BENCHMARKFLAGS)  ; \
	$(CXX) $(CXXFLAGS)  $(MEMORYFLAGS) $(VECTORFLAGS) -o bin/pathfinder_fullvec.exe src/*.o -lm $(BENCHMARKFLAGS) ; \
	rm src/*.o ;

clean:
	rm bin/*.dump; \
	rm bin/*.exe;