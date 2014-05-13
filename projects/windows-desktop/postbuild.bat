@echo off

set ProjectDir=%1%
set OutDir=%2%
set Configuration=%3%

echo "ProjectDir=%ProjectDir%"
echo "OutDir=%OutDir%"
echo "Configuration=%Configuration%"
xcopy /D /Y /E %ProjectDir%..\..\3rdparty\cef3\%Configuration%\*.* %OutDir%
xcopy /D /Y /E %ProjectDir%..\..\3rdparty\cef3\Resources\*.* %OutDir%
rem mkdir %OutDir%\images
xcopy /D /Y /E %ProjectDir%..\..\images\*.* %OutDir%\images\
rem mkdir %OutDir%\sounds
xcopy /D /Y /E %ProjectDir%..\..\images\*.* %OutDir%\sounds\
rem mkdir %OutDir%\www
xcopy /D /Y /E %ProjectDir%..\..\www\*.* %OutDir%\www\
xcopy /D /Y %ProjectDir%..\..\config.xml %OutDir%