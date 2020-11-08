@call "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat"	

rem note
cl -MT -DWIN32 -EHsc -I"D:\madoodia\sdks\Arnold-6.1.0.0\include" -c mkU2Color.cpp
link -nologo -DLL -out:"D:\madoodia\dev\ArnoldShaders\mkU2Color.dll" mkU2Color.obj "D:\madoodia\sdks\Arnold-6.1.0.0\lib\ai.lib"
del mkU2Color.obj
del mkU2Color.lib
del mkU2Color.exp

move mkU2Color.dll "D:\madoodia\dev\ArnoldShaders\mkU2Color.dll"
echo "D:\madoodia\dev\ArnoldShaders\mkU2Color.dll"
