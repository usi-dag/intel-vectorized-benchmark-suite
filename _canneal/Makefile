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
	$(CXX) src/*.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/canneal_serial.exe

autovec:
	$(CXX) src/*.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -o $(BIN)/canneal_autovec.exe

explicitvec:
	$(CXX)  src/*.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -o $(BIN)/canneal_explicitvec.exe

fullvec:
	$(CXX)  src/*.cpp  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o $(BIN)/canneal_fullvec.exe


clean:
	rm $(BIN)/*.exe;

#start:
#	rm bin/*.*;
#
#serial:
#	for entry in src/*.cpp ; do \
#		${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -c -o $$entry.o  $$entry ; \
#	done
#	${GCC}/bin/g++ -march=native -O3 -fno-tree-vectorize -o bin/canneal_serial.exe src/*.cpp.o -lm ; \
##	${GCC}/bin/llvm-objdump  --mattr=+m,+f,+d,+a,+c -ds  bin/canneal_serial.exe > bin/canneal_serial.dump ; \
#	rm src/*.o ; \
#
#vector:
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize -c -o src/annealer_thread.o src/annealer_thread.cpp; \
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize -c -o src/main.o src/main.cpp; \
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize -c -o src/netlist.o src/netlist.cpp; \
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize -c -o src/netlist_elem.o src/netlist_elem.cpp; \
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize -c -o src/rng.o src/rng.cpp; \
#	${GCC}/bin/g++ -march=native -mavx512f -D$(SIZE) -DUSE_RISCV_VECTOR -O3 -fno-tree-vectorize  -o bin/canneal_vector.exe src/*.o -lm; \
##	${GCC}/bin/llvm-objdump  --mattr=+m,+f,+d,+a,+c,+experimental-v -ds  bin/canneal_vector.exe > bin/canneal_vector.dump ; \
#	rm src/*.o;
#
#clean:
#	rm bin/*.dump; \
#	rm bin/*.exe;