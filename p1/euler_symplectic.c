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
  /*The symplectic Euler scheme is basically the same as the Euler scheme with two changes.
   One is that x is implemented in a reverse order than before: x[1] before x[0].
   The other change is that fx is evaluated between the calculation of x[1] and x[0].  This 
   makes the algorithm semi-implicit and gives it its symplectic properties*/
  if((*integrator).n == 2) //if we are integrating a second order ODE
    {
      assert((*integrator).rhs( (*integrator).n,t,x,(*integrator).fx)==0); //find fx and assert success
      x[1] += (*integrator).dt * (*integrator).fx[1]; //Calculate x[1] = x'(t)
      
      assert((*integrator).rhs( (*integrator).n,t,x,(*integrator).fx)==0); //find fx and assert success
      x[0] += (*integrator).dt * (*integrator).fx[0]; //Calculate x[0] = x(t) but with f[0] already advanced a 
                                               //timestep based on x[1], making it an implicit calculation
    }

  else //We are not integrating a second order ODE, so let user know
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
