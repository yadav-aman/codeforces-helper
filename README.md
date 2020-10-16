# Helper bot for codeforces contests

### This script automatically extracts the sample test cases of a given codeforces contest, creates sperate files for inputs and outputs and organises them in sepearte folder (independent of OS).

You can also provide your own template file and the script will create a solution file based on the template file for each question.

## Installation
Make sure python3 is installed in your machine.
- Linux
    ```
    pip3 install -r requirements.txt
    ```
- Windows 
    ```
    pip install -r requirements.txt
    ```

## Usage
- Linux
    ```
    python3 app.py <contest ID or contest URL>
    ```
    Make an executable in linux
    ```
    chmod +x app.py
    ```
    After making the script executable we can directy run the script as
    ```
    ./app.py <contest ID or contest URL>
    ```
- Windows 
    ```
    python app.py <contest ID or contest URL>
    ```
- examples
    ```
    python app.py 1234 
    ```
    ```
    python3 app.py https://codeforces.com/contest/1234
    ```
    ```
    ./app.py 1234
    ```