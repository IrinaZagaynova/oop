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

REM Expect an error when starting with missing file
%Program% pack Text1.txt Text2.txt && goto err
echo Test 2 passed

REM Expect an error when the first command line argument does not pack or unpack
%Program% word Input.txt %temp%\Output.txt && goto err
echo Test 3 passed

REM Pack empty file
%Program% pack Empty.txt %temp%\Output.txt
fc.exe Empty.txt %temp%\Output.txt || goto err
echo Test 4 passed

REM Unpack empty file
%Program% unpack Empty.txt %temp%\Output.txt
fc.exe Empty.txt %temp%\Output.txt || goto err
echo Test 5 passed

REM Pack and unpack file
%Program% pack Input.txt %temp%\packedFile.txt
%Program% unpack %temp%\packedFile.txt %temp%\Output.txt
fc.exe Input.txt %temp%\Output.txt || goto err
echo Test 6 passed

REM Encode more characters than byte size
%Program% pack InputManyRepeatedCharacters.txt %temp%\Output.txt
fc.exe Output.txt  %temp%\Output.txt || goto err
echo Test 7 passed

REM Expect an error when unpacking an odd-sized file
%Program% unpack OddSizedFile.txt %temp%\Output.txt && goto err
echo Test 8 passed

REM Pack 254 characters
%Program% pack Input254.txt %temp%\Output.txt
fc.exe %temp%\Output.txt %temp%\Output254.txt || goto err
echo Test 9 passed

REM Pack 255 characters
%Program% pack Input255.txt %temp%\Output.txt
fc.exe %temp%\Output.txt %temp%\Output255.txt || goto err
echo Test 10 passed

REM Pack 256 characters
%Program% pack Input256.txt %temp%\Output.txt
fc.exe %temp%\Output.txt %temp%\Output256.txt || goto err
echo Test 11 passed

REM Pack 257 characters
%Program% pack Input257.txt %temp%\Output.txt
fc.exe %temp%\Output.txt %temp%\Output257.txt || goto err
echo Test 12 passed
 
REM The tests were successful
echo All tests passed successfuly
exit /B 0

REM If an error
:err
echo Test failed
exit /B 1