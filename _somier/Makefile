SIZE?=VECTOR_SIZE_512
INTEL_INTRINSIC?=mavx512f -mavx512vl -mavx512dq
CXX=g++
CXXFLAGS= -Wall -pedantic  -std=c++11 -O3
VECTORFLAGS= -D$(SIZE) -$(INTEL_INTRINSIC) -DUSE_VECTOR_INTRINSIC
BENCHMARKFLAGS =  -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
MEMORYFLAGS = -DMEMORY_PROFILER
BIN=bin

.PHONY: main.seq.o somier.o utils.o forces.o


LDFLAGS = -lm

start:
	mkdir $(BIN)
	rm $(BIN)/*.exe

serial: somier_serial.exe clean_o
autovec: somier_autovec.exe clean_o
explicitvec: somier_explicitvec.exe clean_o
fullvec: somier_fullvec.exe clean_o

somier_serial.exe: main.seq.o somier_serial.o utils_serial.o forces_serial.o
	$(CXX) $(CXXFLAGS)  $+ $(BENCHMARKFLAGS) $(MEMORYFLAGS) -fno-tree-vectorize $(LDFLAGS) -o  $(BIN)/$@

somier_autovec.exe: main.autovec.o somier_autovec.o utils_autovec.o forces_autovec.o
	$(CXX) $(CXXFLAGS)  $+ $(BENCHMARKFLAGS) $(MEMORYFLAGS)  $(LDFLAGS) -o  $(BIN)/$@

somier_explicitvec.exe: main.explicit.o somier_serial.o utils_serial.o forces_prevec_lmul1_serial.o somier_intr_lmul1_serial.o
	$(CXX) $(CXXFLAGS) $+ $(LDFLAGS) -fno-tree-vectorize $(BENCHMARKFLAGS) $(MEMORYFLAGS) -o $(BIN)/$@

somier_fullvec.exe: main.fullvec.o somier_autovec.o utils_autovec.o forces_prevec_lmul1_autovec.o somier_intr_lmul1_autovec.o
	$(CXX) $(CXXFLAGS) $+ $(BENCHMARKFLAGS) $(MEMORYFLAGS) $(LDFLAGS) -o $(BIN)/$@

main.seq.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) -fno-tree-vectorize   $< $(BENCHMARKFLAGS) $(MEMORYFLAGS) -c  -o $@

main.autovec.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS)   $< $(BENCHMARKFLAGS) $(MEMORYFLAGS) -c  -o $@

main.explicit.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(VECTORFLAGS) -fno-tree-vectorize -c -o $@ $(BENCHMARKFLAGS) $(MEMORYFLAGS) $<

main.fullvec.o: main.cpp utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(VECTORFLAGS) -c -o $@ $(BENCHMARKFLAGS) $(MEMORYFLAGS) $<

somier_serial.o: somier.cpp utils.h
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize $(MEMORYFLAGS) $(IFLAGS) -c -o $@  $<

somier_autovec.o: somier.cpp utils.h
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(MEMORYFLAGS) -c -o $@  $<




somier_intr_lmul1_serial.o: intrinsics/somier_intr_lmul1.cpp intrinsics/somier_v.h utils.h
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) -fno-tree-vectorize $(BENCHMARKFLAGS) $(IFLAGS) -c -o $@ $<

somier_intr_lmul1_autovec.o: intrinsics/somier_intr_lmul1.cpp intrinsics/somier_v.h utils.h
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) $(BENCHMARKFLAGS) $(IFLAGS) -c -o $@ $<



utils_serial.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize -c -o $@  $<

utils_autovec.o: utils.cpp utils.h
	$(CXX) $(CXXFLAGS) -c -o $@  $<



forces_serial.o: forces.cpp utils.h
	$(CXX) $(CXXFLAGS) -fno-tree-vectorize -c -o $@ $<

forces_autovec.o: forces.cpp utils.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<



forces_prevec_lmul1_serial.o: intrinsics/forces_prevec_lmul1.cpp utils.h
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) -fno-tree-vectorize $(BENCHMARKFLAGS) $(IFLAGS) -c -o $@ $<

forces_prevec_lmul1_autovec.o: intrinsics/forces_prevec_lmul1.cpp utils.h
	$(CXX) $(CXXFLAGS) $(VECTORFLAGS) $(BENCHMARKFLAGS) $(IFLAGS) -c -o $@ $<


clean_o:
	rm -f *.o

clean:
	rm -f *.o
	rm -f $(BIN)/*.exe
