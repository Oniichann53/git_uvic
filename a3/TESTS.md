# Tests for `SENG 265`, Assignment #3

* Test 1
    * Input: `aston-martin-release.ics`
    * Expected output: `test01.txt`
    * Command: `./process_cal3 --start=2022/1/1 --end=2022/1/30 --file=aston-martin-release.ics`
    * Test: `./tester.py 1`
  
* Test 2
    * Input: `aston-martin-release.ics`
    * Expected output: `test02.txt`
    * Command: `./process_cal3 --start=2022/2/10 --end=2022/2/10 --file=aston-martin-release.ics`
    * Test: `./tester.py 2`

* Test 3
    * Input: `season-testing.ics`
    * Expected output: `test03.txt`
    * Command: `./process_cal3 --start=2022/1/1 --end=2022/3/15 --file=2022-season-testing.ics`
    * Test: `./tester.py 3`

* Test 4
    * Input: `f1-podcast.ics`
    * Expected output: `test04.txt`
    * Command: `./process_cal3 --start=2022/3/15 --end=2022/12/1 --file=f1-podcast.ics`
    * Test: `./tester.py 4`

* Test 5
    * Input: `2022-f1-races-americas.ics`
    * Expected output: `test05.txt`
    * Command: `./process_cal3 --start=2022/6/1 --end=2022/11/30 --file=2022-f1-races-americas.ics`
    * Test: `./tester.py 5`

* All 5 Tests
    * Test: `./tester.py`