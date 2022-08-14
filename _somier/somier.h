/*************************************************************************
* Somier - RISC-V Vectorized version
* Author: Jesus Labarta
* Barcelona Supercomputing Center
*************************************************************************/

//extern double M;
//extern double dt;
extern double spring_K;
//extern double Xcenter[3];

extern void init_X (int n, double ****X);

extern void compute_forces(int n, double ****X, double ****F);
extern void compute_forces_prevec(int n, double ****X, double ****F);

extern void acceleration(int n, double ****A, double ****F, double M);
extern void velocities(int n,  double ****V,  double ****A, double dt);
extern void positions(int n,  double ****X,  double ****V, double dt);

extern void accel_intr(int n,  double ****A,  double ****F, double M);
extern void vel_intr(int n,  double ****V, double ****A, double dt);
extern void pos_intr(int n,  double ****X, double ****V, double dt);

extern void compute_stats(int n, double ****X, double Xcenter[3]);
