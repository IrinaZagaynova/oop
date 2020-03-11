@echo off

REM The path to the test program is passed through 1 command line argument
SET Program="%~1" 
echo ""

REM Startup protection without argument
if %Program%=="" (
	echo Please specifi path to program
	exit /B1
)

REM Expect an error when starting without command line arguments
%Program% > nul && goto err
echo Test 1 passed

REM If input isn't number
%Program% abc && goto err
echo Test 2 passed

REM If input is more than stoi can convert
%Program% 9999999999 && goto err
echo Test 3 passed

REM If input is more than 255
%Program% 256 && goto err
echo Test 4 passed

REM If input is less than 0
%Program% -1 && goto err
echo Test 5 passed

REM If input is 0
%Program% 0 > %temp%/Output0.txt
fc.exe Output0.txt %temp%/Output0.txt || goto err
echo Test 6 passed

REM If input is 255
%Program% 255 > %temp%/Output255.txt
fc.exe Output255.txt %temp%/Output255.txt || goto err
echo Test 7 passed

REM If input is 4
%Program% 4 > %temp%/Output32.txt
fc.exe Output32.txt %temp%/Output32.txt || goto err
echo Test 8 passed

REM If input is 32
%Program% 32 > %temp%/Output4.txt
fc.exe Output4.txt %temp%/Output4.txt || goto err
echo Test 9 passed

REM If input is 144
%Program% 144 > %temp%/Output9.txt
fc.exe Output9.txt %temp%/Output9.txt || goto err
echo Test 10 passed

REM If input is 9
%Program% 9 > %temp%/Output144.txt
fc.exe Output144.txt %temp%/Output144.txt || goto err
echo Test 11 passed

REM The tests were successful
echo All tests passed successfuly
exit /B 0

REM If an error
:err
echo Test failed
exit /B 1
