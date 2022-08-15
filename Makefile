BASE_DIR := $(shell pwd)
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2
BIN=bin
OUT=out
MACHINE?=LOCAL
ITERATION?= MULTIPLE_ITERATION


APPLICATION_DIRS := _axpy _blackscholes _canneal _jacobi-2d _lavaMD _swaptions _streamcluster _somier _particlefilter _pathfinder

install: axpy blackscholes canneal jacobi-2d lavaMD particlefilter pathfinder somier swaptions streamcluster

axpy blackscholes canneal jacobi-2d lavaMD  pathfinder somier swaptions streamcluster:
	echo Compiling $@ with following options: vector size $(SIZE) and vector architecture $(INTEL_INTRINSIC)
	cd _$@; 			\
	mkdir $(OUT); \
	mkdir $(OUT)/$(MACHINE); \
	mkdir $(OUT)/$(MACHINE)/$(SIZE); \
	make start;			\
	make serial SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); 		\
	make autovec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	make explicitvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	make fullvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	./$(BIN)/$@_serial.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/serial.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/serial.out; \
	./$(BIN)/$@_autovec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/autovec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/autovec.out; \
	./$(BIN)/$@_explicitvec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/explicitvec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/explicitvec.out; \
	./$(BIN)/$@_fullvec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/fullvec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/fullvec.out;

particlefilter:
	echo Compiling $@ with following options: vector size $(SIZE) and vector architecture $(INTEL_INTRINSIC)
	cd _$@; 			\
	mkdir $(OUT); \
	mkdir $(OUT)/$(MACHINE); \
	mkdir $(OUT)/$(MACHINE)/$(SIZE); \
	make start;			\
	make serial SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); 		\
	make autovec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	make explicitvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC) ITERATION=$(ITERATION); \
	make fullvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC) ITERATION=$(ITERATION); \
	./$(BIN)/$@_serial.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/serial.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/serial.out; \
	./$(BIN)/$@_autovec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/autovec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/autovec.out; \
	./$(BIN)/$@_explicitvec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/explicitvec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/explicitvec.out; \
	./$(BIN)/$@_fullvec.exe --benchmark_out=$(OUT)/$(MACHINE)/$(SIZE)/fullvec.json --benchmark_out_format=json | tee $(OUT)/$(MACHINE)/$(SIZE)/fullvec.out;

clean:
	for dir in $(APPLICATION_DIRS) ; do cd $$dir ; make clean ; cd .. ; done
