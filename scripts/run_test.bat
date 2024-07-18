@cd .\AttemptAt3DProject\build\
@drmemory -leaks_only -brief -results_to_stderr -batch -- .\libs\AttemptAt3D\AttemptAt3DExec.exe
@cd ..\..