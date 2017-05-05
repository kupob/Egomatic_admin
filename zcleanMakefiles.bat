del .\makefile*
del /s .\src\makefile*
del /s .\src\vc100*.pdb
del .\ui_*.h

rmdir /s /q "./obj"
rmdir /s /q "./lib"

exit