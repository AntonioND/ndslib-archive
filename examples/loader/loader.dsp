# Microsoft Developer Studio Project File - Name="loader" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=loader - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "loader.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "loader.mak" CFG="loader - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "loader - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "loader - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "loader - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f loader.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "loader.exe"
# PROP BASE Bsc_Name "loader.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "loader.ds.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "loader - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f loader.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "loader.exe"
# PROP BASE Bsc_Name "loader.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "loader"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "loader - Win32 Release"
# Name "loader - Win32 Debug"

!IF  "$(CFG)" == "loader - Win32 Release"

!ELSEIF  "$(CFG)" == "loader - Win32 Debug"

!ENDIF 

# Begin Group "Loader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\boot\gbfs.h
# End Source File
# Begin Source File

SOURCE=.\boot\libgbfs.c
# End Source File
# Begin Source File

SOURCE=.\boot\main.cpp
# End Source File
# Begin Source File

SOURCE=.\boot\Makefile
# End Source File
# End Group
# Begin Group "ndslib"

# PROP Default_Filter ""
# Begin Group "_ARM7"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\audio.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\BIOS.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\clock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\serial.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\touch.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM7\wifi.h
# End Source File
# End Group
# Begin Group "_ARM9"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\BIOS.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\cache.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\console.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\CP15.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\image.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\keys.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\math.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\pcx.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\rand.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\trig_lut.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\video.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ARM9\videoGL.h
# End Source File
# End Group
# Begin Group "_Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\NDS\card.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DMA.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\interrupts.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ipc.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\jtypes.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\memory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\NDS.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\ndsload.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\registers_alt.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\reload.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\system.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\timers.h
# End Source File
# End Group
# Begin Group "_DarkStar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsBlank.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsClickable.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsEnums.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsGfx.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsInput.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsSound.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsSprite.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsSpriteEnum.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsSpriteManager.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\dsSwapScreens.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\huffman.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\vArray.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\vList.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\vName.h
# End Source File
# Begin Source File

SOURCE=..\..\include\NDS\DarkStar\vTypes.h
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
