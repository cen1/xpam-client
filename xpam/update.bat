@echo Off

taskkill /f /im "xpam.exe"
IF EXIST newxpam.exe (
	del xpam.exe
	RENAME newxpam.exe xpam.exe
)
start xpam.exe
