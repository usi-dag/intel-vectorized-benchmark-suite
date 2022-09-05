## IVBench

IVBench is a collection of diverse benchmarks
that exploit the [Intel vector intrinsicc](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html) on typical SIMD workloads.

This benchmark suite includes a version of the workloads of the
[RIVEC](https://github.com/RALC88/riscv-vectorized-benchmark-suite) suite after
converting them to express vector operations with the Intel intrinsic.


### List of benchmarks

The following table is a complete list of benchmarks included in JVBench in alphabetical order.

| Application Name | Application Domain         | Algorithmic Model    | Taken From |
|------------------|----------------------------|----------------------|------------|
| axpy             | High Performance Computing | BLAS                 | RIVEC      |
| blackscholes     | Financial Analysis         | Dense Linear Algebra | PARSEC     |
| canneal          | Engineering                | Unstructured Grids   | PARSEC     |
| jacobi-2D        | Engineering                | Dense Linear Algebra | PolyBench  |
| lavaMD           | Molecular Dynamics         | N-Body               | Rodinia    |
| particlefilter   | Medical Imaging            | Structured Grids     | Rodinia    |
| pathfinder       | Grid Traversal             | Dynamic Programming  | Rodinia    |
| somier           | Physics Simulation         | Dense Linear Algebra | RIVEC      |
| streamcluster    | Data Mining                | Dense Linear Algebra | PARSEC     |
| swaptions        | Financial Analysis         | MapReduce Regular    | PARSEC     |


### Prerequisites
- GCC 4.8 or above


### Obtaining the suite
To run the suite, you can clone the suite from [here](https://github.com/usi-dag/intel-vectorized-benchmark-suite).


### Running the suite
To run a IVBench benchmark, execute the following java command:
```shell
$ make SIZE=<preferred-size> INTEL_INTRINSIC=<vector-flags> <benchmark>
```
where <benchmarks> is the benchmark name that you wish to run, <preferred-size> is the size of the vector and <vector-flags>
are the flags to enable the intel vector intrinsic.

Available configurations:

| Configuration | <vector-flags>                   | <preferred-size>                                  |
|---------------|----------------------------------|---------------------------------------------------|
| AVX512        | "mavx512f -mavx512vl -mavx512dq" | VECTOR_SIZE_512, VECTOR_SIZE_256, VECTOR_SIZE_128 |
| AVX2          | mavx2                            | VECTOR_SIZE_256, VECTOR_SIZE_128                  |
| AVX           | mavx                             | VECTOR_SIZE_128                                   |

For example to run the axpy benchmark on an architecture that support the AVX512 vector instructions:
```shell
$ make SIZE=VECTOR_SIZE_512 INTEL_INTRINSIC="mavx512f -mavx512vl -mavx512dq" axpy
```


### 🤝 Contributing
You are welcome to contribute to this open-source benchmark suite. If you want to add or modify
the code, feel free to fork the repo, create issues and finally a pull request to review your code!