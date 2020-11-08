@ECHO OFF
REM # --------------------- #
REM # (C) 2020 madoodia.com #
REM # --------------------- #

set ROOT=%1
set FOLDER=%2
set FILE_NAME=%3

set PATH=%PATH%;%SDKS_LOCATION%/Arnold-6.1.0.0/bin

@REM kick -l %ROOT%\%FOLDER% %ROOT%\%FOLDER%\%FILE_NAME%.ass