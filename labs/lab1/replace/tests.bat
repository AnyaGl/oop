 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM Replacing an empty string
 %Program% test-data\input1.txt "%TEMP%\output.txt" "" "*" || goto err
 fc test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM Replacing on an empty string
 %Program% test-data\input2.txt "%TEMP%\output.txt" "_" "" || goto err
 fc test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM Replacing a string that is repeated in a replacement string
 %Program% test-data\input3.txt "%TEMP%\output.txt" "ma" "mama" || goto err
 fc test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed

 REM Replacing the substring "1231234" inside the text "12312312345"
 %Program% test-data\input4.txt "%TEMP%\output.txt" "1231234" "*" || goto err
 fc test-data\output4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 4 passed

 REM Replacing a substring at the beginning, middle, and end of a file
 %Program% test-data\input5.txt "%TEMP%\output.txt" "123" "*" || goto err
 fc test-data\output5.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 5 passed
 
 REM Replacing the whole file
 %Program% test-data\input6.txt "%TEMP%\output.txt" "replace all" "*" || goto err
 fc test-data\output6.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 6 passed
 
 REM Replacing a nonexistent substring
 %Program% test-data\input7.txt "%TEMP%\output.txt" "123" "*" || goto err
 fc test-data\output7.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 7 passed

 REM Replacing a substring in an empty file
 %Program% test-data\input8.txt "%TEMP%\output.txt" "123" "*" || goto err
 fc test-data\output8.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 8 passed
 
 REM Copy from nonexistent file
 %Program% MissingFile.txt "%TEMP%\output.txt" "_" "*" && goto err
 echo Test 9 passed

 REM Copy to nonexistent file
 %Program% test-data\input1.txt not:\out.txt "_" "*" && goto err
 echo Test 10 passed

 REM Incorrect command line arguments: missing argument
 %Program% test-data\input1.txt "%TEMP%\output.txt" "*" && goto err
 echo Test 11 passed

 REM Invalid command line arguments: no arguments
 %Program% && goto err
 echo Test 12 passed

 echo All tests passed successfully
 exit /B 0

 :err
 echo Test failed
 exit /B 1