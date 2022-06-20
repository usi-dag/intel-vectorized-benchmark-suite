# Example
# target: dependencies
	# command 1
	# command 2
          # .
          # .
          # .
	# command n
ifdef OUTPUT
override OUTPUT = -DOUTPUT
endif

#C_C = gcc
#C_C = ${LLVM}/bin/clang
C_C = ${GCC}/bin/gcc
#FLAGS = --target=riscv64-unknown-elf  -march=rv64g -mepi -O3 -fno-vectorize
FLAGS = -march=native  -O3 -fno-tree-vectorize
SIZE?=VECTOR_SIZE_512
VECTOR = -mavx512f -DUSE_RISCV_VECTOR -D$(SIZE)

SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin



dump = ${LLVM}/bin/llvm-objdump
OMP_LIB = #-lgomp
OMP_FLAG = #-fopenmp

start:
	rm bin/*.*

serial: main_serial.o ./kernel/kernel_cpu.o ./util/num/num.o ./util/timer/timer.o
	echo serial; \
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize  main.o ./kernel/kernel_cpu.o ./util/num/num.o ./util/timer/timer.o -lm -o bin/lavaMD_serial.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

autovec: main_serial.o ./kernel/kernel_cpu.o ./util/num/num.o ./util/timer/timer.o
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) main.o ./kernel/kernel_cpu.o ./util/num/num.o ./util/timer/timer.o -lm -o bin/lavaMD_serial.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

explicitvec: main_vector.o ./kernel/kernel_vector.o ./util/num/num.o ./util/timer/timer.o
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) -fno-tree-vectorize   main.o ./kernel/kernel_vector.o ./util/num/num.o ./util/timer/timer.o -lm -o bin/lavaMD_vector.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

fullvec: main_vector.o ./kernel/kernel_vector.o ./util/num/num.o ./util/timer/timer.o
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTORFLAGS) main.o ./kernel/kernel_vector.o ./util/num/num.o ./util/timer/timer.o -lm -o bin/lavaMD_vector.exe ; \
	rm *.o ; \
	rm kernel/*.o ;

# compile function files into objects (binaries)
main_serial.o:	main.hpp \
			main.cpp \
			./kernel/kernel_cpu.h \
			./kernel/kernel_cpu.c \
			./util/num/num.h \
			./util/num/num.c \
			./util/timer/timer.h \
			./util/timer/timer.c
	echo main_serial; \
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) ${OUTPUT} main.cpp \
			-c \
			-o main.o \

main_vector.o:
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(VECTOR) ${OUTPUT} main.cpp -c -o main.o

./kernel/kernel_cpu.o:	./kernel/kernel_cpu.h \
						./kernel/kernel_cpu.c
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(MEMORYFLAGS)	./kernel/kernel_cpu.c \
						-c \
						-o ./kernel/kernel_cpu.o

./kernel/kernel_vector.o:	./kernel/kernel_vector.h \
						./kernel/kernel_vector.c
	$(CXX) $(CXXFLAGS)  $(MEMORYFLAGS)  $(VECTOR)	./kernel/kernel_vector.c \
						-c \
						-o ./kernel/kernel_vector.o

./util/num/num.o:	./util/num/num.h \
					./util/num/num.c
	$(CXX) $(CXXFLAGS)  $(MEMORYFLAGS)  ./util/num/num.c \
					-c \
					-o ./util/num/num.o

./util/timer/timer.o:	./util/timer/timer.h \
						./util/timer/timer.c
	$(CXX) $(CXXFLAGS)  $(MEMORYFLAGS)	./util/timer/timer.c \
						-c \
						-o ./util/timer/timer.o

# delete all object and executable files
clean:
	rm	*.o \
		./kernel/*.o \
		./util/num/*.o \
		./util/timer/*.o \
		./util/device/*.o; \
	rm bin/*.dump; \
	rm bin/*.exe;
