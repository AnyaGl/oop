 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM Packing empty input file
 %Program% pack test-data\input1.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM Unpacking empty input file
 %Program% unpack test-data\input1.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM Packing 255 characters
 %Program% pack test-data\input2.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed

 REM Unacking 255 characters
 %Program% unpack test-data\output2.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\input2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 4 passed

 REM Packing 256 characters
 %Program% pack test-data\input3.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 5 passed

 REM Unacking 256 characters
 %Program% unpack test-data\output3.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\input3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 6 passed

 REM Packing 257 characters
 %Program% pack test-data\input4.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 7 passed

 REM Unacking 257 characters
 %Program% unpack test-data\output4.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\input4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 8 passed

 REM Unacking invalid file (odd file length)
 %Program% unpack test-data\input5.txt "%TEMP%\output.txt" && goto err
 echo Test 9 passed

 REM Unacking invalid file (zero)
 %Program% unpack test-data\input6.txt "%TEMP%\output.txt" && goto err
 echo Test 10 passed 

 REM Packing character with code 255
 %Program% pack test-data\input7.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\output7.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 11 passed

 REM Unpacking character with code 255
 %Program% unpack test-data\output7.txt "%TEMP%\output.txt" || goto err
 fc /B test-data\input7.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 12 passed

 REM Invalid mode
 %Program% packk test-data\input1.txt "%TEMP%\output.txt" && goto err
 echo Test 13 passed

 REM Invalid number of arguments
 %Program% test-data\input1.txt "%TEMP%\output.txt" && goto err
 echo Test 14 passed

 echo All tests passed successfully
 exit /B 0

 :err
 echo Test failed
 exit /B 1