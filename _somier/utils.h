
extern void capture_ref_result(double *y, double* y_ref, int n);
extern void print_4D (int n, char*name, double ****y);
extern void capture_4D_ref (int n, double ****y, double ****y_ref);
extern void test_4D_result(int n, double ****y, double ****y_ref);
extern void clear_4D(int n, double ****X);
extern void init_X (int n, double ****X);
extern void boundary(int n, double ****X, double ****V);
extern void force_contribution(int n, double ****X, double ****F,
                   int i, int j, int k, int neig_i, int neig_j, int neig_k);
extern void compute_force_new(int n, double ****X, double ****F);
extern void  print_state(int n, double ****X, double Xcenter[3], int nt);

extern void print_prv_header();
extern void print_prv_record();
