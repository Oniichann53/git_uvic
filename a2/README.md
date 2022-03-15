# Assignment 2 (A#2)

## Updating provided files

To get the latest version of the provided files for A#2 without replacing the content that might be already present in your process_cal2.py, you can use the following commands:

In any folder outside your a2 folder in your local repository (to avoid replacing potential existing work in process_cal2.py):

    scp NETLINKID@seng265.seng.uvic.ca:/seng265work/2022-spring/a2/* .

    cp *.xml ~/NETLINKID/a2

    cp *.yaml ~/NETLINKID/a2

    cp *.md ~/NETLINKID/a2

The commands above assume you have cloned your repository in the home folder and that you're executing them inside Senjhalla. An analogous process (by replacing the paths) can be followed by students with M1 Macbooks.

## Installing additional modules for tester.py

To use tester.py inside Senjhalla  or in the analogous environment for M1 MacBoocks, you need to execute the following commands

    pip3 install deepdiff
    pip3 install pyyaml

pip3 should be part of the installation you completed for A#0, but if this step failed during the process, you can install pip3 as follows:

* In Senjhalla:

        sudo apt update
        sudo apt install python3-pip

* In M1 Mackbooks: pip3 was automatically installed by homebrew

## Interpreting the diffs produced by tester.py

The easiest way to undersand the differences described by tester.py is to consider the produced output.yaml and the expected .yaml (e.g., test02.yaml) files as dictionaries. Thus, tester.py will tell you when one key in a dictionary is missing in the other one, or when the value associated with a key (e.g., a string or a list) is different from the other side. Also, tester.py checks the syntax of your produced output.yaml file. If the syntax is not valid, the comparisson won't take place.
