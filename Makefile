BASE_DIR := $(shell pwd)
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2


APPLICATION_DIRS := _axpy _blackscholes _canneal _jacobi-2d _lavaMD _swaptions _streamcluster _somier _particlefilter _pathfinder

all: axpy blackscholes canneal jacobi-2d lavaMD particlefilter pathfinder somier swaptions streamcluster

axpy blackscholes canneal jacobi-2d lavaMD particlefilter pathfinder somier swaptions streamcluster:
	cd _$@; 			\
	make start;			\
	make serial SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); 		\
	make autovec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	make explicitvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); \
	make fullvec SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC);