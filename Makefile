BASE_DIR := $(shell pwd)
SIZE?=VECTOR_SIZE_256
INTEL_INTRINSIC?=mavx2


APPLICATION_DIRS := _axpy _blackscholes _canneal _jacobi-2d _lavaMD _swaptions _streamcluster _somier _particlefilter _pathfinder

all: axpy  # vblackscholes canneal jacobi-2d lavaMD swaptions streamcluster somier particlefilter pathfinder

axpy:
	cd _axpy; 			\
	make start;			\
	make vector SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC); 		\
	make serial SIZE=$(SIZE) INTEL_INTRINSIC=$(INTEL_INTRINSIC);