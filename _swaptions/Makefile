#makefile
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -O3 -g
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

start:
	mkdir $(BIN); \
	rm $(BIN)/*.*

serial:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS)  -fno-tree-vectorize src/*.cpp $(BENCHMARKFLAGS) -o $(BIN)/swaptions_serial.exe

autovec:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS) src/*.cpp $(BENCHMARKFLAGS) -o $(BIN)/swaptions_autovec.exe

explicitvec:
	for entry in src/*.cpp ; do \
	  $(CXX) $(CXXFLAGS) -fno-tree-vectorize  $(VECTORFLAGS) $(MEMORYFLAGS) -c $(BENCHMARKFLAGS) -o  $$entry.o  $$entry ; \
	done
	$(CXX)  $(CXXFLAGS)  $(VECTORFLAGS) $(MEMORYFLAGS) -o bin/swaptions_explicitvec.exe src/*.cpp.o $(BENCHMARKFLAGS) -lm;	\
	rm src/*.o; \

fullvec:
	for entry in src/*.cpp ; do \
	  $(CXX) $(CXXFLAGS) -fno-tree-vectorize  $(VECTORFLAGS) $(MEMORYFLAGS) -c $(BENCHMARKFLAGS) -o  $$entry.o  $$entry ; \
	done
	$(CXX)  $(CXXFLAGS)  $(VECTORFLAGS) $(MEMORYFLAGS) -o bin/swaptions_fullvec.exe src/*.cpp.o $(BENCHMARKFLAGS) -lm;	\
	rm src/*.o; \

clean:
	rm $(BIN)/*.exe;
