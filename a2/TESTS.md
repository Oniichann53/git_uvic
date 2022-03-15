# Tests for `SENG 265`, Assignment #2

* Test 1
    * Inputs: `2022-season-testing.xml, circuits.xml, broadcasters.xml`
    * Expected output: `test01.yaml`
    * Command: `./process_cal2.py --start=2022/12/1 --end=2022/12/30 --events=2022-season-testing.xml --circuits=circuits.xml --broadcasters=broadcasters.xml`
    * Test: `./tester.py test01.yaml`

* Test 2
    * Input: `2022-season-testing.xml, circuits.xml, broadcasters.xml`
    * Expected output: `test02.yaml`
    * Command: `./process_cal2.py --start=2022/2/25 --end=2022/3/15 --events=2022-season-testing.xml --circuits=circuits.xml --broadcasters=broadcasters.xml`
    * Test: `./tester.py test02.yaml`

* Test 3
    * Input: `2022-season-testing.xml, circuits.xml, broadcasters.xml`
    * Expected output: `test03.yaml`
    * Command: `./process_cal2.py --start=2022/2/1 --end=2022/3/9 --events=2022-season-testing.xml --circuits=circuits.xml --broadcasters=broadcasters.xml`
    * Test: `./tester.py test03.yaml`

* Test 4
    * Input: `2022-f1-races-americas.xml, circuits.xml, broadcasters.xml`
    * Expected output: `test04.yaml`
    * Command: `./process_cal2.py --start=2022/2/1 --end=2022/7/1 --events=2022-f1-races-americas.xml --circuits=circuits.xml --broadcasters=broadcasters.xml`
    * Test: `./tester.py test04.yaml`

* Test 5
    * Input: `2022-f1-races-americas.xml, circuits.xml, broadcasters.xml`
    * Expected output: `test05.yaml`
    * Command: `./process_cal2.py --start=2022/1/1 --end=2022/12/31 --events=2022-f1-races-americas.xml --circuits=circuits.xml --broadcasters=broadcasters.xml`
    * Test: `./tester.py test05.yaml`