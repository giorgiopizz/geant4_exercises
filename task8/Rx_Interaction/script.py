import os
import subprocess


mixture = [
    'Kr70_CO230',
    'Ar70_CO230',
    'Kr100',
    'Xe70_CO230',
    'Xe100'
]

def name(i, energy):
    return 'electrons_'+mixture[int(i)-1]+'_'+energy

l = [
    # ['1', '4000'],
    # ['1', '14000'],
    # ['1', '18000'],
    # ['2', '2000'],
    # ['2', '5000'],
    # ['3', '10000'],
    # ['3', '15000'],
    # ['4','10000'],
    # ['4', '20000'],
    # ['5', '18000'],
    ['5', '20000']
]

for pars in l:
    print("ESEGUO PER: ")
    print(name(*pars))
    ex = ["./electrons"]+ pars + [name(*pars)]
    print( ex )
    proc = subprocess.Popen(ex)
    proc.wait()
