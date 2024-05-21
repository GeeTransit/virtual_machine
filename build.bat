@echo off

set MYCD=%cd%
mkdir debug
pushd debug

set SRC=..\src\*.c

clang-cl %SRC% /link /OUT:main.exe
popd
