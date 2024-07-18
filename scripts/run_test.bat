@cd .\AttemptAt3DProject\build\
@echo ======================================================================================
@echo ===== REMINDER: Dr. Memory can make the program much slower, so give it a second =====
@echo ======================================================================================
@drmemory -leaks_only -brief -results_to_stderr -batch -- .\libs\AttemptAt3D\AttemptAt3DExec.exe
@cd ..\..