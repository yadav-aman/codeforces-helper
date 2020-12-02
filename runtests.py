#!/usr/bin/env python3

import sys
import os
import subprocess
import re

def display_result(expected_output,your_output,test_case_no):
    with open(expected_output) as file:
        ex_out = file.read().strip()

    with open(your_output) as file:
        y_out = file.read().strip()

    with open('result.txt','a') as file:
        if ex_out == y_out:
            res = "\nTestcase "+test_case_no+" passed\n"
            print(res)
            res+='Your Output\n'+y_out+'\n'
            file.write(res)
        else:
            res = f'''\nTestcase {test_case_no} failed\n
Expected Output of test case {test_case_no} :
{ex_out}
\nYour Output of test case {test_case_no} :
{y_out}
\n---------------------------------------------
'''

            print(res)

            file.write(res)


if __name__ == '__main__':
    try:
        directory = sys.argv[1].lower()
        os.chdir(directory)
        # create blank result.txt file
        with open('result.txt','w') as file:
            pass
    except IndexError:
        print("Please pass probem-name(case insensitive) as command line argument  eg: ./runtests.py a")
        sys.exit(1)
    except FileNotFoundError:
        print("Directory",directory,"not found")
        sys.exit(1)

    print("Compling solution.cpp")
    exit_status = subprocess.run(["g++",'solution.cpp'])
    if exit_status.returncode == 0:
        print("Compilation successful\n")
    else:
        print("Compilation error")
        sys.exit(1)

    files = os.listdir()
    input_files = [x for x in files if 'input' in x]
    output_files =  [x for x in files if 'output' in x]
    your_files = []

    for x in input_files:
        file_no = re.search(r'\d+',x)[0]
        your_outputfile = "out"+file_no+".txt"
        your_files.append(your_outputfile)
        if os.name == 'nt': # windows
            # cmd.exe /c "a.exe < input.txt > output.txt"
            command = f'a.exe < {x} > {your_outputfile}'
            subprocess.run(['cmd.exe','/c',command])
        else:
            command = f'./a.out < {x} > {your_outputfile}'
            subprocess.run(["sh",'-c',command])

        display_result(f'output{file_no}.txt',your_outputfile,file_no)

        your_outputfile = ''

    print("Results saved to result.txt")

    os.chdir('..')
