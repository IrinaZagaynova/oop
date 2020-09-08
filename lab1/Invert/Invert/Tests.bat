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

REM Expect an error when starting the program with missing file
%MyProgram% Input.txt && goto err
echo Test 2 passed

REM Expect an error when starting the program with 2 argument
%Program% Matrix3x3 Matrix3x3 && goto err
echo Test 3 passed

REM If input is 3x3 matrix
%Program% Matrix3x3.txt > %temp%\Output.txt
fc.exe OutputMatrix3x3.txt %temp%\Output.txt || goto err
echo Test 4 passed

REM If input is 3x4 matrix
%Program% Matrix3x4.txt > %temp%\Output.txt
fc.exe OutputIfInvalidMatrix.txt %temp%\Output.txt || goto err
echo Test 5 passed

REM If input is 3x2 matrix
%Program% Matrix3x2.txt > %temp%\Output.txt
fc.exe OutputIfInvalidMatrix.txt %temp%\Output.txt || goto err
echo Test 6 passed

REM If input is 5x3 matrix
%Program% Matrix5x3.txt > %temp%\Output.txt
fc.exe OutputIfInvalidMatrix.txt %temp%\Output.txt || goto err
echo Test 7 passed

REM If input is 2x3 matrix
%Program% Matrix2x3.txt > %temp%\Output.txt
fc.exe OutputIfInvalidMatrix.txt %temp%\Output.txt || goto err
echo Test 8 passed

REM If input is a matrix containing letters
%Program% MatrixContainingLetters.txt > %temp%\Output.txt
fc.exe OutputIfInvalidMatrix.txt %temp%\Output.txt || goto err
echo Test 9 passed

REM If the input is a matrix with a zero determinant
%Program% MatrixWithZeroDeterminant.txt > %temp%\Output.txt
fc.exe OutputIfZeroDeterminant.txt %temp%\Output.txt || goto err
echo Test 9 passed

REM The tests were successful
echo All tests passed successfuly
exit /B 0

REM If an error
:err
echo Test failed
exit /B 1