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
        if type != 'euler_symplectic':
            pp.plot(t,x,label=labelstring)
        elif value == 10000:
            pp.plot(t,x,label=labelstring,lw=4)
        elif value == 1000:
            pp.plot(t,x,label=labelstring,lw=8)
        else:
            pp.plot(t,x,label=labelstring)
            


    pp.plot(np.linspace(0.,100.,1000),analytic(np.linspace(0.,100.,1000)),label="True")
    pp.xlabel("t")
    pp.ylabel("f(x)")
    pp.legend(loc='best')
    pp.title(type)
    s = 'pdf/' + type + '_plot.pdf'
    pp.savefig(s)
    pp.close()
        
#Now plot for a given nsteps all the types

for value in num:
    for type in ('euler', 'euler_symplectic', 'rk4'):
        s = type + '.' + str(value) + '.out'
        t,x,xprime = np.loadtxt(s,unpack=True)
        pp.plot(t,x,label=type)

    pp.plot(np.linspace(0.,100.,100000),analytic(np.linspace(0.,100.,100000)),label="True")
    pp.xlabel("t")
    pp.ylabel("f(x)")
    #pp.xlim(0,20)
    pp.ylim(-0.12,0.12)
    pp.legend(loc='best')
    titlestring = 'Nsteps = ' + str(value)
    pp.title(titlestring)
    s = 'pdf/' + str(value) + '_plot.pdf'
    pp.savefig(s)
    pp.close()

ntemp=1000000
pp.plot(np.linspace(0.,100.,ntemp),analytic(np.linspace(0.,100.,ntemp)),label="True")
pp.xlabel("t")
pp.xlim(0,20)
pp.ylabel("true f(x)")
pp.title("True")
s = 'pdf/true_plot.pdf'
pp.savefig(s)
pp.close()
