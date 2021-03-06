@echo off

set DEVENV=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe
if exist "%DEVENV%" goto devenv_found

set DEVENV=C:\Program Files(x86)\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe
if exist "%DEVENV%" goto devenv_found

echo "Please set DEVENV to the location of the devenv.exe program.
got end

:devenv_found

echo "Removing old artifacts"
del output /s /q
del CMakeCache.txt /q
del CMakeFiles /s /q
if not exist output mkdir output

echo "Building UnitTest++"
cd 3rd-party\UnitTest++

"%DEVENV%" UnitTest++.vsnet2008.sln /Rebuild Debug
"%DEVENV%" UnitTest++.vsnet2008.sln /Rebuild Release

cd ..\..
echo "Running CMake"
cmake CMakeLists.txt

echo "Building Libamqp"
"%DEVENV%" libamqp.sln /Rebuild Debug
"%DEVENV%" libamqp.sln /Build Debug /project RUN_TESTS

:end
