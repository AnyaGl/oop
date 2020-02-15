 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM Замена пустой строки
 %Program% test-data\input1.txt "%TEMP%\output.txt" "" "*" || goto err
 fc test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM Замена на пустую строку
 %Program% test-data\input2.txt "%TEMP%\output.txt" "_" "" || goto err
 fc test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM Замена строки, которая многократно входит в строку-заменитель
 %Program% test-data\input3.txt "%TEMP%\output.txt" "ma" "mama" || goto err
 fc test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed

 REM Замена подстроки "1231234" внутри текста "12312312345"
 %Program% test-data\input4.txt "%TEMP%\output.txt" "1231234" "*" || goto err
 fc test-data\output4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 4 passed

 REM Замена подстроки, находящейся в начале, середине и конце файла
 %Program% test-data\input5.txt "%TEMP%\output.txt" "123" "*" || goto err
 fc test-data\output5.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 5 passed
 
 REM Замена строки, из которой состоит файл
 %Program% test-data\input6.txt "%TEMP%\output.txt" "replace all" "*" || goto err
 fc test-data\output6.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 6 passed
 
 REM Замена подстроки, которой нет в файле
 %Program% test-data\input7.txt "%TEMP%\output.txt" "123" "*" || goto err
 fc test-data\output7.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 7 passed
 
 REM Копирование из несуществующего файла
 %Program% MissingFile.txt "%TEMP%\output.txt" "_" "*" && goto err
 echo Test 8 passed

 REM Неверно заданные аргументы командной строки: нет одного из файлов
 %Program% test-data\input1.txt "_" "*" && goto err
 echo Test 9 passed

 REM Неверно заданные аргументы командной строки: нет одной из строк
 %Program% test-data\input1.txt "%TEMP%\output.txt" "*" && goto err
 echo Test 10 passed

 REM Неверно заданные аргументы командной строки: нет ни одного аргумента
 %Program% && goto err
 echo Test 11 passed

 echo All tests passed successfully
 exit /B 0

 :err
 echo Test failed
 exit /B 1