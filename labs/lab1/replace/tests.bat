 @echo off
 
 SET Program="%~1"

 if %Program%=="" (
    echo Please specify path to program 
    exit /B 1
 )

 REM ������ ������ ������
 %Program% test-data\input1.txt "%TEMP%\output.txt" "" "*" || goto err
 fc test-data\output1.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 1 passed

 REM ������ �� ������ ������
 %Program% test-data\input2.txt "%TEMP%\output.txt" "_" "" || goto err
 fc test-data\output2.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 2 passed

 REM ������ ������, ������� ����������� ������ � ������-����������
 %Program% test-data\input3.txt "%TEMP%\output.txt" "ma" "mama" || goto err
 fc test-data\output3.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 3 passed

 REM ������ ��������� "1231234" ������ ������ "12312312345"
 %Program% test-data\input4.txt "%TEMP%\output.txt" "1231234" "*" || goto err
 fc test-data\output4.txt "%TEMP%\output.txt" > nul || goto err
 echo Test 4 passed

 REM ����������� �� ��������������� �����
 %Program% MissingFile.txt "%TEMP%\output.txt" "_" "*" && goto err
 echo Test 5 passed

 REM ������� �������� ��������� ��������� ������: ��� ������ �� ������
 %Program% test-data\input1.txt "_" "*" && goto err
 echo Test 6 passed

 REM ������� �������� ��������� ��������� ������: ��� ����� �� �����
 %Program% test-data\input1.txt "%TEMP%\output.txt" "*" && goto err
 echo Test 7 passed

 REM ������� �������� ��������� ��������� ������: ��� �� ������ ���������
 %Program% && goto err
 echo Test 8 passed

 echo All tests passed successfully
 exit /B 0

 :err
 echo Test failed
 exit /B 1