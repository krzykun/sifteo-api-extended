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
	cd ..
	echo.
	echo Rebuild finished sucessfully!
	GOTO end
:EndScript
	echo.
	echo Script ended
	echo Please specify a directory (project name) as a parameter
	echo.
:end