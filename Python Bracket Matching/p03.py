from Stack03 import Stack
import sys

def is_balanced(candidate):
    s = Stack()
    for i in range(0, len(candidate)):
        if candidate[i] == '{' or candidate[i] == '[' or candidate[i] == '(':
                s.push(candidate[i])
        elif candidate[i] == '}':
            open_bracket = s.pop()
            if open_bracket != '{':
                return False
        elif candidate[i] == ']':
            open_bracket = s.pop()
            if open_bracket != '[':
                return False
        elif candidate[i] == ')':
            open_bracket = s.pop()
            if open_bracket != '(':
                return False
    return s.is_empty()

"""
brackies = '(({}[{(){}}]))'
if is_balanced(brackies):
    print(brackies, ' is balanced')
else:
    print(brackies, ' is not balanced')
"""

argc = len(sys.argv) - 1
ifn = ''
ofn = ''

try:
    if argc == 0:
        ifn = input('Enter the input file name: ')
        ofn = input('Enter the output file name: ')
    elif argc == 1:
        ifn = sys.argv[1]
        ofn = input('Enter the output file name: ')
    elif argc == 2:
        ifn = sys.argv[1]
        ofn = sys.argv[2]
    else:
        raise Exception('Error: Too many command line arguments.')
except Exception as ex:
    print(ex)

#TODO: open the input file, read each line, and test balance
infile = open(ifn, "r")
outfile = open(ofn, "w+")
lines = infile.readlines()
for line in lines:
    p = line.replace("\n", "")
    if is_balanced(line):
        outfile.write(p + ' is matching\n')
    else:
        outfile.write(p + ' is not matching\n')
outfile.close()
infile.close()
#TODO: write results to output file
