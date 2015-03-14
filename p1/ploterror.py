import numpy as np
import matplotlib.pyplot as pp

num=[1000,10000,100000]

for type in ('euler', 'euler_symplectic', 'rk4'):
    for value in num:
        s = type + '.error.' + str(value) + '.out'
        error = np.loadtxt(s,unpack=True)
        labelstring = 'Nsteps = ' + str(value)
        pp.plot(np.linspace(0.,100.,value+1),error,label=labelstring)


    pp.xlabel("t")
    pp.ylabel("Error")
    pp.yscale('log')
    pp.legend(loc='best')
    pp.title(type)
    s = 'pdf/' + type + '_error_plot.pdf'
    pp.savefig(s)
    pp.close()
        
#Now plot for a given nsteps all the types

for value in num:
    for type in ('euler', 'euler_symplectic', 'rk4'):
        s = type + '.error.' + str(value) + '.out'
        error = np.loadtxt(s,unpack=True)
        pp.plot(np.linspace(0.,100.,value+1),error,label=type)


    pp.xlabel("t")
    pp.ylabel("Error")
    pp.yscale('log')
    pp.legend(loc='best')
    titlestring = 'Nsteps = ' + str(value)
    pp.title(titlestring)
    s = 'pdf/' + str(value) + '_error_plot.pdf'
    pp.savefig(s)
    pp.close()
