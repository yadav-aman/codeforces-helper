#!/usr/bin/env python3

#importing libraries
import urllib.request
import sys
from bs4 import BeautifulSoup
import re
import os
from shutil import copyfile

# Get data from url
def get_page_data(url):
    try:
        url_contents = urllib.request.urlopen(url).read()
        soup = BeautifulSoup(url_contents,"html.parser") 
        return soup
    except:
        print("Unable to connect to the site. Please check your internet connection")
        sys.exit(1)

#Extract links of questions
def get_question_links(soup):
    links = []
    pattern = r"/contest/\d+(/problem/[A-Z0-9]+)"
    for link in soup.findAll('a'):
        res = re.search(pattern,str(link))
        if res and res[1] not in links:
            links.append(res[1])
    return links

# extract sample test cases from webpage
def get_sample_test(soup):
    sample_tests = soup.find("div",{"class": "sample-test"})
    if sample_tests:
        if sample_tests.find('br'):
            sample_tests = sample_tests.get_text("\n").strip()
        else:
            sample_tests = sample_tests.get_text().strip()

    return sample_tests

# create files and directories of the given competition
def create_files(problem_question_dir,problem_name,test_cases):
    file_num_input = 1
    file_num_output = 1
    file_data = ""

    test_split = test_cases.split('\n')
    problem_dir = os.path.join(problem_question_dir,problem_name)
    try:
        os.mkdir(problem_dir)
    except:
        print("Directory",problem_name,"already exists..\nPerforming following tasks in",problem_name)
    
    if not os.path.exists(os.path.join(problem_dir,'solution.cpp')):
        print('Copying C++ template file to',problem_dir)
        try :
            copyfile('template.cpp',os.path.join(problem_dir,'solution.cpp'))
        except:
            print("Error copying, no template file found")
    else:
        print("Solution file already exists")

    i=0
    while i < len(test_split):
        if test_split[i] == 'Input':
            file_name = os.path.join(problem_dir,'input'+str(file_num_input)+'.txt')
            i+=1
            file_num_input+=1

            while test_split[i] != 'Output':
                file_data += str(test_split[i])+'\n'
                i+=1

            with open(file_name,'w') as file:
                print('Writing',file_name)
                file.write(file_data)
                file_data = ""

        if test_split[i] == 'Output':
            file_name = os.path.join(problem_dir,'output'+str(file_num_output)+'.txt')
            i+=1
            file_num_output+=1

            while i < len(test_split) and test_split[i] != 'Input':
                file_data += str(test_split[i])+'\n'
                i+=1

            with open(file_name,'w') as file:
                print('Writing',file_name)
                file.write(file_data)
                file_data = ""
    print("File creation for problem",problem_dir,"completed..\n")

# driver function
if __name__ == '__main__':
    try:
        contest_id = sys.argv[1]
    except:
        print("Please provide contest ID or URL of codeforces contest as command line argument")
        sys.exit(1)
    if 'https://codeforces.com/contest/' in contest_id:
        url = contest_id
    else:
        url = 'https://codeforces.com/contest/'+contest_id

    if not re.search(r"https://codeforces.com/contest/\d+",url):
        print("Please enter a vaid link")
        sys.exit(1)

    html_data = get_page_data(url)
    question_links = get_question_links(html_data)

    problem_question_dir = re.search(r'\d+',url)[0]
    
    try:
        os.mkdir(problem_question_dir)
    except:
        print("Directory",problem_question_dir,"already exists..\nPerforming following tasks in",problem_question_dir,"\n")

    try:
        print("Copying runtest.py to",problem_question_dir,"\n")
        copyfile('runtests.py',os.path.join(problem_question_dir,'runtests.py'))
    except:
        print("Script to run test cases not found\n")

    for link in question_links:
        question_page_data = get_page_data(url+link)
        test_cases = get_sample_test(question_page_data)
        if not test_cases:
            print("No test cases found")
            sys.exit(1)
        create_files(problem_question_dir,re.search(r"[A-Z0-9]+",link)[0].lower(),test_cases)
