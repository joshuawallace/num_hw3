/* Author Joshua Wallace
   Originally created Sept. 23 2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "integrator.h"


//stuff to be carried between integrator steps
struct integrator_t {
  int n; //degree of ODE
  double dt; //timestep size
  double *fx; //values found by solving ODE
  FuncPtr rhs; //the (possibly coupled) ODE function(s)
};

//creates a new Integrator object
Integrator *integrator_new(int n_, double dt_, FuncPtr rhs_)
{
  Integrator *in = malloc(sizeof(Integrator)); //allocates memory for Integrator
  (*in).fx = malloc(n_*sizeof(double)); //fx must be allocated at runtime based on n_
  assert(in!=NULL);
  (*in).n = n_;  //degree of ODE to be integrated
  (*in).dt=dt_;  //the timestep size
  (*in).rhs=rhs_;// the (coupled, possibly) ODE's to be integrated
  
  return in;
}


//steps the integrator forward one step
int integrator_step(Integrator *integrator, double t, double *x)
{
  if((*integrator).n == 2)
    {
      assert((*integrator).rhs( (*integrator).n,t,x,(*integrator).fx)==0); //find fx and assert success
      x[1] += (*integrator).dt * (*integrator).fx[1];
      
      assert((*integrator).rhs( (*integrator).n,t,x,(*integrator).fx)==0); //find fx and assert success
      x[0] += (*integrator).dt * (*integrator).fx[0];
    }
  else
    {
      printf("Didn't recognize dimension size given to symplectic_euler integrator\n");
      return 1;
    }
 
  return 0;
}

//frees all the relevant memory tied up in Integrator
void integrator_free(Integrator *integrator)
{
  free( (*integrator).fx);
  free(integrator);
}
