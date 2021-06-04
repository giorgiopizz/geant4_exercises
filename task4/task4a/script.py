import re
with open('log.txt','r') as file:
    a = file.read()
    p = re.compile('process\[([a-zA-Z: ]*)\]')
    matches = re.findall(p,a)
    for match in matches:
        print('\item '+ match)
