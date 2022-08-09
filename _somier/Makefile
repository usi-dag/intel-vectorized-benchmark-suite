CFLAGS += -march=native  -O3 -fno-tree-vectorize

LDFLAGS = -lm -static
IFLAGS = -I ./ -I ${VEHAVE_TOOLCHAIN}/include/vehave/ -I ${VEHAVE_TOOLCHAIN}/include/vehave-user/

#makefile
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = #-DMEMORY_PROFILER
BIN=bin

start:
	mkdir $(BIN)
	rm $(BIN)/*.exe
	rm $(BIN)/*.dump

serial: somier_serial.exe somier_serial.dump clean_o

autovec: somier_autovec.exe somier_serial.dump clean_o

explicitvec: somier_explicitvec.exe somier_vector.dump clean_o

fullvec: somier_fullvec.exe somier_vector.dump clean_o

somier_serial.exe: main.seq.o somier.o utils.o forces.o
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize -o $@ $(BIN)/$+ $(LDFLAGS)

somier_autovec.exe: main.seq.o somier.o utils.o forces.o
	$(CXX) $(CXXFLAGS) -o $@ $(BIN)/$+ $(LDFLAGS)

somier_explicitvec.exe: main.vec.o somier.o utils.o forces_prevec_lmul1.o somier_intr_lmul1.o
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) -fno-tree-vectorize -o $@ $(BIN)$+ $(LDFLAGS)

somier_fullvec.exe: main.vec.o somier.o utils.o forces_prevec_lmul1.o somier_intr_lmul1.o
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS)  -o $@ $(BIN)$+ $(LDFLAGS)

main.seq.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(IFLAGS) -DSEQ -c -o $@ $<

main.vec.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(BENCHMARKFLAGS) $(VECTORFLAGS) $(IFLAGS) -c -o $@ $<

somier.o: omp/somier.c utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c -o $@ $<

somier_intr_lmul1.o: intrinsics/somier_intr_lmul1.c intrinsics/somier_v.h utils.h
	$(CXX) $(CXXFLAGS)  $(VECTORFLAGS) $(IFLAGS) -c -o $@ $<

utils.o: utils.c utils.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

forces.o: forces.c utils.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

forces_prevec_lmul1.o: intrinsics/forces_prevec_lmul1.c utils.h
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) $(IFLAGS) -c -o $@ $<


clean_o:
	rm -f *.o

clean:
	rm -f *.o
	rm -f *.exe
