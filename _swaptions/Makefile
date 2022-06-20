#makefile
SIZE?=VECTOR_SIZE_512
INTEL_INTRINSIC?=mavx512f
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

start:
	mkdir $(BIN); \
	rm $(BIN)/*.*

#serial:
#	for entry in src/*.cpp ; do \
#		$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) -fno-tree-vectorize -c -o  $$entry.o  $$entry ; \
#	done
#	$(CXX)  $(CXXFLAGS) $(BENCHMARKFLAGS) -fno-tree-vectorize -o bin/swaptions_serial.exe src/*.cpp.o -lm;	\

serial:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) src/*.cpp -o $(BIN)/swaptions_serial.exe
	rm src/*.o; \

vector:
	for entry in src/*.cpp ; do \
	  $(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -c -o  $$entry.o  $$entry ; \
	done
	$(CXX)  $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -o bin/swaptions_vector.exe src/*.cpp.o -lm;	\
	rm src/*.o; \

clean:
	rm $(BIN)/*.exe;
