SIZE?=VECTOR_SIZE_512
INTEL_INTRINSIC?=mavx512f -mavx512vl -mavx512dq
CXX=g++
CXXFLAGS= -Wall -pedantic  -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

start:
	mkdir $(BIN)
	rm $(BIN)/*.*

serial:
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/axpy_serial.exe

autovec:
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS)  -o $(BIN)/axpy_autovec.exe

explicitvec:
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/axpy_explicitvec.exe

fullvec:
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o $(BIN)/axpy_fullvec.exe


clean:
	rm $(BIN)/*.exe;