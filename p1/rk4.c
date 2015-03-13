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
  int n;  //degree of ODE
  double dt; //timestep size
  FuncPtr rhs; //the (possibly coupled) ODE function(s)
};

//creates a new Integrator object
Integrator *integrator_new(int n_, double dt_, FuncPtr rhs_)
{
  
  Integrator *in = malloc(sizeof(Integrator)); //allocates memory for Integrator
  assert(in!=NULL);
  (*in).n = n_;   //degree of ODE to be integrated
  (*in).dt=dt_;  //the timestep size
  (*in).rhs=rhs_;// the (coupled, possibly) ODE's to be integrated  
  
  return in;
}


//steps the integrator forward one step
int integrator_step(Integrator *integrator, double t, double *x)
{
  
  //the output values of the rhs function
  double fx[(*integrator).n];
  
  //the k values needed for the Runge-Kutta algorithm
  //first index corresponds to the order of the equation,
  //second index to the subscript of k, appropriately indexed
  double k[(*integrator).n][4];
  
  assert((*integrator).rhs( (*integrator).n,t,x,fx)==0);
  
  //calculates k1, based on fx above
  for(int i=0;i<(*integrator).n;i++)
    {
      k[i][0]=fx[i];
    }
  
  
  //allows us to set x to feed in to the rhs function as x + h/2 * k_1
  //since k_1 is going to be different for each of the n elements of x
  double xtofeedin[(*integrator).n];
  
  for(int i=0;i<(*integrator).n;i++)
    {
      xtofeedin[i]=x[i]+(*integrator).dt/2 * k[i][0];
    }
  
  assert((*integrator).rhs( (*integrator).n,t+(*integrator).dt/2,xtofeedin,fx)==0);
  
  //calculates k2, based on fx above, which was based on xtofeedin above
  for(int i=0;i<(*integrator).n;i++)
    {
      k[i][1]=fx[i];
    }
  
  
  //Now for k_3
  //First, xtofeedin
  for(int i=0;i<(*integrator).n;i++)
    {
      xtofeedin[i]=x[i]+(*integrator).dt/2 * k[i][1];
    }
  
  assert((*integrator).rhs( (*integrator).n,t+(*integrator).dt/2,xtofeedin,fx)==0);
  
  //calculates k3, based on fx above, which was based on xtofeedin above
  for(int i=0;i<(*integrator).n;i++)
    {
      k[i][2]=fx[i];
    }
  
  
  //Now for k_4
  //First, xtofeedin
  for(int i=0;i<(*integrator).n;i++)
    {
      xtofeedin[i]=x[i]+(*integrator).dt * k[i][2];
    }
  
  assert((*integrator).rhs( (*integrator).n,t+(*integrator).dt,xtofeedin,fx)==0);
  
  //calculates k3, based on fx above, which was based on xtofeedin above
  for(int i=0;i<(*integrator).n;i++)
    {
      k[i][3]=fx[i];
    }
  
  /////////////////Now to actually update the x values
  
  for(int i=0;i<(*integrator).n;i++)
    {
      x[i] = x[i] + (*integrator).dt/6.*k[i][0] + (*integrator).dt/3.*(k[i][1] + k[i][2]) + (*integrator).dt/6.*k[i][3];
    }
  return 0;
}

//frees all the relevant memory tied up in Integrator
void integrator_free(Integrator *integrator)
{
  free(integrator);
}
