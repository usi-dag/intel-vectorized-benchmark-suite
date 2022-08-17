SIZE?=VECTOR_SIZE_128
INTEL_INTRINSIC?=mavx512f -mavx512vl -mavx512dq
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
	$(CXX) src/jacobi-2d.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/jacobi-2d_serial.exe

autovec:
	$(CXX) src/jacobi-2d.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -o $(BIN)/jacobi-2d_autovec.exe

explicitvec:
	$(CXX) src/jacobi-2d.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/jacobi-2d_explicitvec.exe

fullvec:
	$(CXX) src/jacobi-2d.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o $(BIN)/jacobi-2d_fullvec.exe


clean:
	rm $(BIN)/*.exe;