import csv
from colorama import Fore, Back, Style

def read_from_file():
    with open('report.txt') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        passed = 0
        failed = 0
        for row in csv_reader:
                passed = passed + int(row[0])
                failed = failed + int(row[1])
        return passed, failed

def main():
    passed, failed = read_from_file()
    print("{}RESULT: ( {}{} Passed, {}{} Failed{} )\n".format(Style.BRIGHT ,Fore.GREEN, passed, Fore.RED,failed, Fore.WHITE))

if __name__ == "__main__":
    main()