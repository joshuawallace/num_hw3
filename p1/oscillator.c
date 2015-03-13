/* Author Joshua Wallace
   Originally created Sept. 23 2014
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "integrator.h"

//prints this message if there aren't the right number of command line arguments
void intromessage(char *name)
{
  printf("Usage: %s, number of steps\n",name);
  exit(0);
}

//This is the coupled first order ODE's you get for solving the forced  oscillator
int thefunction(int n, double t, const double *x, double *fx)
{
  //oscillator specific implementation:
  if(n!=2)
    {
      printf("I was expecting n to be 2, not %d.\n Please reconcile.  This is an  oscillator, only a second order ODE.\n Now quitting the function...",n);
      return -1;
    }

  //parameters for the equation
  //const double m=1.0; //Since this parameter is just 1, I will ignore it since it only comes in as a multiplication
  const double omega=0.1;
  const double omega_n_squared=25.;
  fx[0]=x[1];
  fx[1]=-omega_n_squared*x[0] + cos(omega*t);
  return 0;
}

int main(int argc, char **argv)
{
  //iteration counters
  int i;

  //dimension variable;
  const int n=2;

  //initial conditions
  const double x_initial=0.;
  const double x_prime_initial=0.;

  //make sure there were the right number of command line arguments
  if(argc!=2) intromessage(argv[0]);

  //read in the command line arguments, give them variable names
  const double time_max=100.;
  const int    n_steps=atoi(argv[1]);
  const double h=time_max/atof(argv[1]);

  //The values x and y=x' in an array, the values as expressed in the function
  double x[n];

  //initialize them to the initial values
  //x[0] is the x value, x[1] is the x'=y value
  x[0]=x_initial;
  x[1]=x_prime_initial;


  //Creates a pointer to a struct of type integrator_t, which is defined in the various integrator files
  Integrator *integrator_struct;
  
  //allocated memory, start things up
  integrator_struct = integrator_new(n,h,thefunction);

  //Keep track of time
  double t=0.;

  //print out the initial values
  printf("%15.8f %15.8f %15.8f\n",t,x[0],x[1]);

  //print the results out in form: t x x'
  //each line a different timestep
  for(i=0;i<n_steps;i++)
    {
      assert(integrator_step(integrator_struct,t,x) ==0); //steps y, which is x'
      t+=h;
      printf("%15.8f %15.8f %15.8f\n",t,x[0],x[1]); //prints out the results
    }

  //free the memory up for others to use
  integrator_free(integrator_struct);

  return 0;
}
