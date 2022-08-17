#makefile
SIZE?=VECTOR_SIZE_512
INTEL_INTRINSIC?=mavx512f -mavx512vl -mavx512dq
CXX=g++
CXXFLAGS= -Wall  -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

start:
	mkdir $(BIN)
	rm $(BIN)/*.*

serial:
	$(CXX) src/blackscholes.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/blackscholes_serial.exe

autovec:
	$(CXX) src/blackscholes.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -o $(BIN)/blackscholes_autovec.exe


explicitvec:
	$(CXX)  src/blackscholes.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/blackscholes_explicitvec.exe

fullvec:
	$(CXX)  src/blackscholes.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o $(BIN)/blackscholes_fullvec.exe


clean:
	rm $(BIN)/*.exe;
