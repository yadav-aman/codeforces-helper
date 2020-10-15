# Helper bot for codeforces contests

### This script automatically extracts the sample test cases of a given codeforces contest, creates sperate files for input and output and organise them in sepearte folder.

You can also provide your own template file and the script will create a solution file based on the template file for each question.

## Installation
- Linux
    ```
    pip3 install -r requirements.txt
    python3 app.py <contest ID or contest URL>
    ```
- Windows 
    ```
    pip install -r requirements.txt
    python app.py <contest ID or contest URL>
    ```
- examples
    ```
    python app.py 1320 
    ```
    ```
    python3 app.py https://codeforces.com/contest/1320
    ```
