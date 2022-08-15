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
	mkdir $(BIN)
	rm $(BIN)/*.*

serial:
	$(CXX) src/streamcluster.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/streamcluster_serial.exe

autovec:
	$(CXX) src/streamcluster.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -o $(BIN)/streamcluster_autovec.exe


explicitvec:
	$(CXX)  src/streamcluster.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/streamcluster_explicitvec.exe

fullvec:
	$(CXX)  src/streamcluster.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o $(BIN)/streamcluster_fullvec.exe


clean:
	rm $(BIN)/*.exe;
