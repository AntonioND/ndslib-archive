# Microsoft Developer Studio Project File - Name="MultiNDS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=MultiNDS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultiNDS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiNDS.mak" CFG="MultiNDS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiNDS - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "MultiNDS - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "MultiNDS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f MultiNDS.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "MultiNDS.exe"
# PROP BASE Bsc_Name "MultiNDS.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "MultiNDS.ds.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "MultiNDS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f MultiNDS.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "MultiNDS.exe"
# PROP BASE Bsc_Name "MultiNDS.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "MultiNDS"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "MultiNDS - Win32 Release"
# Name "MultiNDS - Win32 Debug"

!IF  "$(CFG)" == "MultiNDS - Win32 Release"

!ELSEIF  "$(CFG)" == "MultiNDS - Win32 Debug"

!ENDIF 

# Begin Group "ARM7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm7\main.c
# End Source File
# Begin Source File

SOURCE=.\arm7\Makefile
# End Source File
# End Group
# Begin Group "ARM9"

# PROP Default_Filter ""
# Begin Group "gbfs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\gbfs\COPYING
# End Source File
# Begin Source File

SOURCE=.\arm9\gbfs\COPYING.DJ
# End Source File
# Begin Source File

SOURCE=.\arm9\gbfs\gbfs.h
# End Source File
# Begin Source File

SOURCE=.\arm9\gbfs\libgbfs.c
# End Source File
# Begin Source File

SOURCE=.\arm9\gbfs\readme.txt
# End Source File
# Begin Source File

SOURCE=.\arm9\gbfs\COPYING.LIB
# End Source File
# End Group
# Begin Source File

SOURCE=.\arm9\common.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\common.h
# End Source File
# Begin Source File

SOURCE=.\arm9\irq.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\letters.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\letters.h
# End Source File
# Begin Source File

SOURCE=.\arm9\main.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\main.h
# End Source File
# Begin Source File

SOURCE=.\arm9\Makefile
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsFade.h
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsGame.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsGame.h
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsLoadGame.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsLoadGame.h
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsMenu.h
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsMove.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\mndsMove.h
# End Source File
# Begin Source File

SOURCE=.\arm9\palette_themes.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\palette_themes.h
# End Source File
# End Group
# Begin Group "ndslib"

# PROP Default_Filter ""
# Begin Group "_ARM7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\audio.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\BIOS.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\clock.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\serial.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\touch.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM7\wifi.h
# End Source File
# End Group
# Begin Group "_ARM9"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\BIOS.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\console.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\CP15.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\math.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\rand.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\trig_lut.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\video.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ARM9\videoGL.h
# End Source File
# End Group
# Begin Group "_Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ndslib\include\NDS\card.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DMA.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\interrupts.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\ipc.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\jtypes.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\memory.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\NDS.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\registers_alt.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\system.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\timers.h
# End Source File
# End Group
# Begin Group "_LIB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ndslib\lib\ARM9\CP15.S
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\CommonMakefile.in
# End Source File
# Begin Source File

SOURCE=.\icon.bmp
# End Source File
# Begin Source File

SOURCE=.\License.txt
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\MakeResources.in
# End Source File
# End Target
# End Project
