@echo off
	IF [%1] == [] GOTO EndScript
	cd %1
	echo.
	echo Cleaned files:
	for %%A in (*.d, *.o, *.elf, *.gen.*) do (
		echo %%~nxA
		del %%A
	)
	echo.
	make
	Siftulator %1.elf
	
	cd ..
	GOTO end
:EndScript
	echo.
	echo Script ended
	echo Please specify a directory (project name) as a parameter
	echo.
:end