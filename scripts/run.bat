@cd .\AttemptAt3DProject\build\
@REM @.\libs\AttemptAt3D\AttemptAt3DExec.exe
@REM @ninja test
ctest -T memcheck -D CTEST_MEMORYCHECK_COMMAND=""
@cd ..\..