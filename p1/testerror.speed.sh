#!/bin/csh

foreach n ( 100)
  echo $n
    foreach name (euler euler_symplectic rk4)
      echo $name
      ./oscillator_$name $n
   end
end