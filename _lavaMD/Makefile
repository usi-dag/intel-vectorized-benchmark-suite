ifdef OUTPUT
override OUTPUT = -DOUTPUT
endif

SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS= -Wall -pedantic  -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin


start:
	rm $(BIN)/*.*

serial: main_serial.o ./kernel/kernel_cpu_serial.o
	$(CXX) $(CXXFLAGS)  main.o ./kernel/kernel_cpu.o $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -lm -o $(BIN)/lavaMD_serial.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

autovec: main_autovec.o ./kernel/kernel_cpu_autovec.o
	$(CXX) $(CXXFLAGS)  main.o ./kernel/kernel_cpu.o $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -lm -o $(BIN)/lavaMD_autovec.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

explicitvec: main_vector_explicit.o ./kernel/kernel_vector_explicit.o
	$(CXX) $(CXXFLAGS)  main.o ./kernel/kernel_vector.o $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize -lm -o   $(BIN)/lavaMD_explicitvec.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

fullvec: main_vector_full.o ./kernel/kernel_vector_full.o
	$(CXX) $(CXXFLAGS)  main.o ./kernel/kernel_vector.o $(BENCHMARKFLAGS)  $(MEMORYFLAGS) -lm -o   $(BIN)/lavaMD_fullvec.exe ; \
	rm *.o ; \
	rm kernel/*.o ;


# compile function files into objects (binaries)
main_serial.o:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS)   ${OUTPUT} main.cpp $(BENCHMARKFLAGS) -fno-tree-vectorize -c -o main.o

main_autovec.o:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS)   ${OUTPUT} main.cpp $(BENCHMARKFLAGS) -c -o main.o

main_vector_explicit.o:
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS)  $(MEMORYFLAGS) ${OUTPUT} main.cpp $(BENCHMARKFLAGS) -fno-tree-vectorize -c -o main.o

main_vector_full.o:
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS)  $(MEMORYFLAGS) ${OUTPUT} main.cpp $(BENCHMARKFLAGS) -fno-tree-vectorize -c -o main.o

./kernel/kernel_cpu_serial.o:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize ./kernel/kernel_cpu.cpp \
						-c \
						-o ./kernel/kernel_cpu.o

./kernel/kernel_cpu_autovec.o:
	$(CXX) $(CXXFLAGS) $(MEMORYFLAGS)  ./kernel/kernel_cpu.cpp \
						-c \
						-o ./kernel/kernel_cpu.o

./kernel/kernel_vector_explicit.o:
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize	./kernel/kernel_vector.cpp \
						-c \
						-o ./kernel/kernel_vector.o

./kernel/kernel_vector_full.o:
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize	./kernel/kernel_vector.cpp \
						-c \
						-o ./kernel/kernel_vector.o


# delete all object and executable files
clean:
	rm	*.o \
		./kernel/*.o ; \
	rm $(BIN)/*.dump; \
	rm $(BIN)/*.exe;
