#ifndef INTEGRATOR_H
#define INTEGRATOR_H

// Pointer to a function that computes
// fx = f(x,t)
// where n is the dimension of the state x
// should return 0 if successful, nonzero if error
typedef int (*FuncPtr)(int n, double t, const double *x, double *fx);
typedef struct integrator_t Integrator;

// Return a new Integrator object
// n: dimension of state vector
// dt: timestep
// rhs: pointer to a function to compute right-hand side of \dot x = f(x,t)
Integrator *integrator_new(int n, double dt, FuncPtr rhs);

// Free the Integrator object and any associated memory
void integrator_free(Integrator *integrator);

// Advance x by one timestep
int integrator_step(Integrator *integrator, double t, double *x);
#endif
