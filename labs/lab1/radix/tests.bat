 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM Convert INT_MAX
 %Program% 10 2 2147483647 > "%TEMP%\output.txt" || goto err
 fc test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM Convert INT_MIN
 %Program% 10 2 -2147483648 > "%TEMP%\output.txt" || goto err
 fc test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM Convert zero
 %Program% 10 2 0 > "%TEMP%\output.txt" || goto err
 fc test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed

 REM Convert of a number containing letters of different register and numbers
 %Program% 16 8 1aF > "%TEMP%\output.txt" || goto err
 fc test-data\output4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 4 passed

 REM Convert negative number
 %Program% 16 36 -1aF > "%TEMP%\output.txt" || goto err
 fc test-data\output5.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 5 passed

 REM Overflow (positive number)
 %Program% 10 8 2147483648 && goto err
 echo Test 6 passed

 REM Overflow (negative number)
 %Program% 10 8 -2147483649 && goto err
 echo Test 7 passed

 REM Invalid character
 %Program% 10 8 12*3 && goto err
 echo Test 8 passed

 REM Invalid character (digit)
 %Program% 3 8 312 && goto err
 echo Test 9 passed

 REM Invalid character (letter)
 %Program% 11 8 a1b && goto err
 echo Test 10 passed

 REM Invalid source radix
 %Program% 37 8 123 && goto err
 echo Test 11 passed

 REM Invalid destination radix
 %Program% 3 1 12112 && goto err
 echo Test 12 passed

REM Invalid command line arguments
%Program% 3 12112 && goto err
echo Test 13 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1