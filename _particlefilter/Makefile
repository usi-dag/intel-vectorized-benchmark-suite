SIZE?=VECTOR_SIZE_512
INTEL_INTRINSIC?=mavx512f -mavx512vl -mavx512dq
CXX=g++
CXXFLAGS= -Wall -g -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
ITERATION?= MULTIPLE_ITERATION
ITERATION_FLAGS = -D$(ITERATION)
BIN=bin

start:
	mkdir $(BIN)
	rm $(BIN)/*.*

serial:
	$(CXX) src/particlefilter.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/particlefilter_serial.exe

autovec:
	$(CXX) src/particlefilter.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -o $(BIN)/particlefilter_autovec.exe

explicitvec:
	$(CXX) src/particlefilter.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) $(ITERATION_FLAGS) -fno-tree-vectorize -o $(BIN)/particlefilter_explicitvec.exe

fullvec:
	$(CXX) src/particlefilter.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) $(ITERATION_FLAGS) -o $(BIN)/particlefilter_fullvec.exe


clean:
	rm $(BIN)/*.exe;
	