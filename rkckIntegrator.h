#ifndef __rkckIntegrator__
#define __rkckIntegrator__

#define TimebaseScaler 1000

void rkck(double y, double dydx, double h, double *m, double *merr, double c);
void rkstep(double y, double dydx, double htry, double eps, double mscal, int *hdid, 
            double *hnext, double c, double *mdid, double *epsdid);

void ODESolve(int *hdid, double *hnext, double htry, int *qdid, double c, double eps,
               int qstart);

#define MAXSTP 10000
#define TINY 1.0E-30
#define SAFTY 0.9
#define PGROW -0.2
#define PSHRNK -0.25
#define ERRCON 1.89E-4

#define QuantumSize 1E-8
#define HalfQuantumSize QuantumSize/2.0

#endif __rkckIntegrator__
