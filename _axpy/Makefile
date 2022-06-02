SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS=-g -Wall -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
BIN=bin

start:
	rm $(BIN)/*.*

serial:
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) -fno-tree-vectorize -o $(BIN)/axpy_serial.exe


vector:
	echo $(INTEL_INTRINSIC)
	$(CXX) src/axpy_benchmark.cpp src/axpy.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) -o $(BIN)/axpy_vector.exe


clean:
	rm $(BIN)/*.exe;