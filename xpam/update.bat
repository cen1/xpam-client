@echo Off

ping 127.0.0.1 -n 3 > nul
IF EXIST newxpam.exe (
	del xpam.exe
	RENAME newxpam.exe xpam.exe
)
start xpam.exe
