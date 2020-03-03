 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM Matrix containing fractional numbers
 %Program% test-data\input1.txt > "%TEMP%\output.txt" || goto err
 fc test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM Identity matrix
 %Program% test-data\input2.txt > "%TEMP%\output.txt" || goto err
 fc test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM Input file contains more elements than required
 %Program% test-data\input3.txt > "%TEMP%\output.txt" || goto err
 fc test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed
 
 REM Singular matrix
 %Program% test-data\input4.txt > "%TEMP%\output.txt" || goto err
 echo Test 4 passed

 REM Input file contains invalid character (minus)
 %Program% test-data\input5.txt > "%TEMP%\output.txt" && goto err
 echo Test 5 passed

 REM Input file contains invalid character (letter)
 %Program% test-data\input6.txt > "%TEMP%\output.txt" && goto err
 echo Test 6 passed

 REM Invalid input file (less elements than required)
 %Program% test-data\input7.txt > "%TEMP%\output.txt" && goto err
 echo Test 7 passed 

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1