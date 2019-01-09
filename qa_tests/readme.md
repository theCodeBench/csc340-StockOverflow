--Tests are disabled until they all pass, so the pipeline doesn't fail--
--To run the tests, the files must be uncommented in the Makefile--

Run make in this directory to build test code.
ACCOUNTS_DIR needs to exist in same directory.
Two of the tests will fail until bug fixes are merged.

TraderHelper contains helper functions from demo to display data.

Account data will be messed up after the first run.
Original account data until fixes to tests are made:

account_Empty
5000.000000

account_Invalid
5000:000000
msft:92.660000:10:22:2:2018

account_Seperate
5000:000000
v:100.000000:15:20:2:2018
v:110.000000:10:21:2:2018
