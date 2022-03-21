#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on  Fri Mar 04 11:07:27 2022
@author: rivera

This tester file allows to validate the correctness of the process_cal3 program
"""
import sys
import os
from pathlib import Path


def run_one(command, expected_file_path, show_diffs):
    """Allows to run one test and compare its output against the expect one.

    Parameters
    ----------
    command : str, required
        The command to run for the test.
    expected_file_path: str, required
        The path of the file that contains the expected output for the test.
    show_diffs: bool, required
        Indicates whether to show or not the list of differences found during the test.
    """
    result = True
    file_to_generate = 'output.txt'
    original_command = command
    command = command + ' > ' + file_to_generate
    print_message(is_error=False, message='Attempting "' + command + '" and expecting ' + expected_file_path + '...')
    # running the command
    os.system(command)
    # validating execution
    if not os.path.isfile(file_to_generate):
        print_message(is_error=True, message=original_command + ' FAILED. See details above.')
    else:
        # compare lines
        print_message(is_error=False, message='Comparing lines...')
        diffs = []
        # get the content of the files
        produced_lines = read_file(file_to_generate)
        expected_lines = read_file(expected_file_path)
        # get the number of lines of produced and expected files
        lines_produced = len(produced_lines)
        lines_expected = len(expected_lines)
        # get the list to navigate
        list_to_navigate = None
        if lines_produced >= lines_expected:
            list_to_navigate = produced_lines
        else:
            list_to_navigate = expected_lines
        # compare each line
        for index in range(len(list_to_navigate)):
            produced_line = 'N/A'
            expected_line = 'N/A'
            if index < lines_produced:
                produced_line = produced_lines[index]
            if index < lines_expected:
                expected_line = expected_lines[index]
            # format the lines
            produced_line_formatted = format_line(produced_line)
            expected_line_formatted = format_line(expected_line)
            if not produced_line_formatted == expected_line_formatted:
                    diffs.append((str(index+1), produced_line, expected_line))
        # print results
        if len(diffs) > 0:
            result = False
            print_message(is_error=False, message='TEST FAILED for ' + expected_file_path + '.')
            if show_diffs:
                 print_message(is_error=False, message='Differences shown below (line_index, produced_line, expected_line):')
                 print(diffs)
        else:
            print_message(is_error=False, message='TEST PASSED for ' + expected_file_path + '.')
    return result      


def read_file(file_path):
    """Allows to read the lines of a text-based file.

    Parameters
    ----------
    file_path : str, required
        The path to the file to read.

    Returns
    -------
    lines
        A list of strings tha represent the lines read.
    """
    lines = []
    file = open(file_path, "r")
    for line in file:
        lines.append(line)
    file.close()
    return lines


def format_line(line):
    """Allows to format a string line to replace spaces with a special character.

    Parameters
    ----------
    line : str, required
        The line to format.

    Returns
    -------
    line
        A formated line.
    """
    return line.rstrip('\n').replace(" ", "%")


def run_all(tests):
    """Allows to run all the tests for the assignment.

    Parameters
    ----------
    tests : List, required
        The list of tests to run.
    """
    num_passed = 0
    for test in tests:
        passed = run_one(command=test[0], expected_file_path=test[1], show_diffs=False)
        if passed:
            num_passed += 1
        print('----------------------------------------------------------')
    print_message(is_error=False, message='# tests passed: ' + str(num_passed) + '/' + str(len(tests)) + ' (' + str(int((num_passed/len(tests))*100)) + '%)')


def print_message(is_error, message):
    """Allows to print a relevant menssage to the user.

    Parameters
    ----------
    is_error : bool, required
        Indicates the type of message.
    message : str, required
        The message to display.
    """
    type = None
    if is_error:
        type = 'ERROR'
    else:
        type = 'INFO'
    print(sys.argv[0] + ' (' + type + '):', message)


def main():
    """The entry point of the script.

    Parameters
    ----------
    test : int, optional
        Indicates if a specific test needs to be executed.
    """
    # relevant variables
    tests = [
        ('./process_cal3 --start=2022/1/1 --end=2022/1/30 --file=aston-martin-release.ics', 'test01.txt'),
        ('./process_cal3 --start=2022/2/10 --end=2022/2/10 --file=aston-martin-release.ics', 'test02.txt'),
        ('./process_cal3 --start=2022/1/1 --end=2022/3/15 --file=2022-season-testing.ics', 'test03.txt'),
        ('./process_cal3 --start=2022/3/15 --end=2022/12/1 --file=f1-podcast.ics', 'test04.txt'),
        ('./process_cal3 --start=2022/6/1 --end=2022/11/30 --file=2022-f1-races-americas.ics', 'test05.txt')
    ]
    file_to_run = 'process_cal3'
    build_folder = Path(os.getcwd())
    compiled_file_path = os.path.join(build_folder, file_to_run)
    # validate compilation
    if not os.path.isfile(compiled_file_path):
        print_message(is_error=True, message='File ' + file_to_run + ' was not found. ' + 'Make sure to use make to compile your program first.')
    else:
            if len(sys.argv) == 1:
                run_all(tests=tests)       
            else:
                run_one(command=tests[int(sys.argv[1])-1][0], expected_file_path=tests[int(sys.argv[1])-1][1], show_diffs=True)


if __name__ == '__main__':
    main()