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

#start:
#	rm bin/*.*
#
#serial:
#	${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -c -o src/streamcluster_serial.o src/streamcluster.cpp
#	${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -o bin/streamcluster_serial.exe src/streamcluster_serial.o -lm
#	rm src/*.o
#	#${GCC}/bin/llvm-objdump  --mattr=+m,+f,+d,+a,+c -ds  bin/streamcluster_serial.exe > bin/streamcluster_serial.dump
#
#vector:
#	${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -DUSE_RISCV_VECTOR -D$(SIZE) -mavx512f -c -o src/streamcluster.o src/streamcluster.cpp
#	${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -DUSE_RISCV_VECTOR -D$(SIZE) -mavx512f -o bin/streamcluster_vector.exe src/*.o -lm
#	rm src/*.o
#	#${GCC}/bin/llvm-objdump  --mattr=+m,+f,+d,+a,+c,+experimental-v -ds   bin/streamcluster_vector.exe > bin/streamcluster_vector.dump
#
#clean:
#	rm bin/*.dump
#	rm bin/*.exe