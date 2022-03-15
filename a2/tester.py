#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Feb 01 07:35:33 2022
@author: rivera

This tester file allows to validate the correctness of the produced output.yaml files
"""
import sys
import yaml
from deepdiff import DeepDiff


def print_message(message):
    """Gets the data from a .yaml file.

    Parameters
    ----------
    message : str, required
        The message to display.
    """
    print('[' + sys.argv[0] + ']:', message)


def read_yaml_data(file):
    """Gets the data from a .yaml file.

    Parameters
    ----------
    file : str, required
        The file path of the file to read.

    Raises
    ------
    FileNotFoundError
        If no file is found.
    yaml.scanner.ScannerError
        If the .yaml file contains errors
    """
    with open(file, 'r') as stream:
        return yaml.safe_load(stream)


def compare_file_content(given_file_data, expected_data):
    """Gets the data from a .yaml file.

    Parameters
    ----------
    given_file_data : dict, required
        A dictionary with the data from the given file (output.yaml)
    expected_data : dic, required
        A dictionary with the data from expected output file (e.g., test01.yaml)
    """
    return DeepDiff(expected_data, given_file_data, ignore_order=False)


def main():
    """The main entry point for the program.

    It requires the input file to be named as output.yaml and a file that contains the expected output for the test
    (e.g., test01.yaml) as an argument for the program
    """
    # Validate arguments
    if not len(sys.argv) == 2:
        print_message('Usage: ' + sys.argv[0] + ' <expected-output-yaml>')
    else:
        # Get the arguments for the app
        given_output_file_path = 'output.yaml'
        expected_output_file_path = sys.argv[1]
        try:
            # Obtain the yaml data
            given_file_data = read_yaml_data(given_output_file_path)
            expected_data = read_yaml_data(expected_output_file_path)
            # Obtain the differences
            result = compare_file_content(given_file_data, expected_data)
            if len(result) > 0:
                print_message('TEST FAILED.' + ' Differences are shown below:')
                print(result)
            else:
                print_message('TEST PASSED')
        except FileNotFoundError as fnf:
            print(print_message('ERROR: ' + fnf.strerror))
        except yaml.scanner.ScannerError as sce:
            print(print_message('ERROR: ' + 'A provided .yaml file contains syntax errors (i.e., invalid YAML file): '
                                + str(sce)))


if __name__ == '__main__':
    main()
