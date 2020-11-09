@ECHO OFF
REM # --------------------- #
REM # (C) 2020 madoodia.com #
REM # --------------------- #

set ROOT=%1
set FOLDER=%2
set FILE_NAME=%3

@REM echo %ROOT%
@REM echo %FOLDER%
@REM echo %FILE_NAME%

@REM ------------------------------------
@REM Download newest Arnold SDK from arnoldrenderer.com
@REM unzip it in a directory

set PATH=%PATH%;%SDKS_LOCATION%/Arnold-6.1.0.0/bin

set VCVARS_LOCATION="C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build"

call %VCVARS_LOCATION%/vcvarsall.bat x64

@REM compile
cl -c %ROOT%/%FOLDER%/%FILE_NAME%.cpp /I. /I%SDKS_LOCATION%/Arnold-6.1.0.0/include /DUNICODE /DWIN32 /D_WIN64 /D_WINDOWS /MT /EHsc /O2 /FC /Zi /Fo:%ROOT%/%FOLDER%/%FILE_NAME%.obj

@REM link
link %ROOT%/%FOLDER%/%FILE_NAME%.obj /out:%ROOT%/%FOLDER%/%FILE_NAME%.dll /nologo /machine:x64 /dll %SDKS_LOCATION%/Arnold-6.1.0.0/lib/ai.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

devenv %ROOT%/%FOLDER%/%FILE_NAME%.dll