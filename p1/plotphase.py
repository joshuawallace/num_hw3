import numpy as np
import matplotlib.pyplot as pp

omega = .1
omega_n = 5
def analytic(t):
    return (np.cos(omega*t) - np.cos(omega_n*t) ) / (omega_n * omega_n - omega * omega)

num=[1000,10000,100000]

for type in ('euler', 'euler_symplectic', 'rk4'):
    for value in num:
        s = type + '.' + str(value) + '.out'
        t,x,xprime = np.loadtxt(s,unpack=True)
        labelstring = 'Nsteps = ' + str(value)
        #if type != 'euler_symplectic':
        #    pp.plot(x,xprime,label=labelstring)
        if value == 10000:
            pp.plot(x,xprime,label=labelstring,lw=2.5)
        elif value == 1000:
            pp.plot(x,xprime,label=labelstring,lw=2)
        else:
            pp.plot(x,xprime,label=labelstring)
            


#    pp.plot(np.linspace(0.,100.,1000),analytic(np.linspace(0.,100.,1000)),label="True")
    pp.xlabel("position")
    pp.ylabel("velocity")
    pp.xlim(-.1,.1)
    pp.ylim(-.3,.3)
    if type == 'euler':
        pp.xlim(-1,1)
        pp.ylim(-1,1)
    pp.legend(loc='best')
    pp.title(type)
    s = 'pdf/' + type + '_phase_plot.pdf'
    pp.savefig(s)
    pp.close()
        
#Now plot for a given nsteps all the types

for value in num:
    for type in ('euler', 'euler_symplectic', 'rk4'):
        s = type + '.' + str(value) + '.out'
        t,x,xprime = np.loadtxt(s,unpack=True)
        if type == 'euler_symplectic':
            pp.plot(x,xprime,label=type,lw=4)
        else:
            pp.plot(x,xprime,label=type)

    #pp.plot(np.linspace(0.,100.,100000),analytic(np.linspace(0.,100.,100000)),label="True")
    pp.xlabel("position")
    pp.ylabel("velocity")
    pp.xlim(-.2,.15)
    pp.ylim(-1,1)
    pp.legend(loc='best')
    titlestring = 'Nsteps = ' + str(value)
    pp.title(titlestring)
    s = 'pdf/' + str(value) + '_phase_plot.pdf'
    pp.savefig(s)
    pp.close()


