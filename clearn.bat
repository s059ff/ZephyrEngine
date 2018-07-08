echo off
for /d %%a in (*) do (call :sub "%%a")
rd /s /q "Debug"
rd /s /q "Release"
rd /s /q "x64"
rd /s /q "x86"
rd /s /q "html"
rd /s /q ".vs"
del /q "*.sdf"
del /q "*.db"
del /q "*.opendb"
echo on
goto end

:sub
cd %~1
rd /s /q "bin"
rd /s /q "obj"
rd /s /q "Debug"
rd /s /q "Release"
rd /s /q "x64"
rd /s /q "x86"
cd ..
exit /b

:end
del /q "*.db"
pause