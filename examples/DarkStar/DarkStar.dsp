# Microsoft Developer Studio Project File - Name="DarkStar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=DarkStar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DarkStar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DarkStar.mak" CFG="DarkStar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DarkStar - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "DarkStar - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "DarkStar - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f DarkStar.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "DarkStar.exe"
# PROP BASE Bsc_Name "DarkStar.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "DarkStar.ds.gba"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "DarkStar - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f DarkStar.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "DarkStar.exe"
# PROP BASE Bsc_Name "DarkStar.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "make"
# PROP Rebuild_Opt "clean"
# PROP Target_File "DarkStar"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "DarkStar - Win32 Release"
# Name "DarkStar - Win32 Debug"

!IF  "$(CFG)" == "DarkStar - Win32 Release"

!ELSEIF  "$(CFG)" == "DarkStar - Win32 Debug"

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
# Begin Group "DarkStar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\DarkStar\DarkStar2.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsApp.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsAppMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsAppMenu.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsBlank.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsBox.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsBox.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsClickable.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsClickable.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsEnums.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsGfx.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsGfx.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsInput.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMain.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMain.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMainMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMainMenu.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSound.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSound.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSprite.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSprite.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSpriteEnum.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSpriteManager.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSpriteManager.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSwapScreens.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsSwapScreensBtn.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsText.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\dsText.h
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\palette_themes.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\DarkStar\palette_themes.h
# End Source File
# End Group
# Begin Group "dsDebug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\dsDebug\dsDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsDebug\dsDebug.h
# End Source File
# End Group
# Begin Group "dsPaint"

# PROP Default_Filter ""
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintBoxTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintBoxTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintCircleTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintCircleTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintDrawTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintDrawTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintDropperTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintDropperTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintFillTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintFillTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintLineTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintLineTool.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaint.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaint.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintClear.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintClear.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintColor.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintColor.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintSlider.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintSubTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintSubTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintTool.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintTool.h
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintUndo.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\dsPaint\dsPaintUndo.h
# End Source File
# End Group
# Begin Group "Check"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\checksout\checksout.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\checksout\checksout.h
# End Source File
# Begin Source File

SOURCE=.\arm9\checksout\checksoutBox.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\checksout\checksoutBox.h
# End Source File
# Begin Source File

SOURCE=.\arm9\checksout\checksoutLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\checksout\checksoutLevel.h
# End Source File
# End Group
# Begin Group "Mines"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\mines\mines.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\mines\mines.h
# End Source File
# End Group
# Begin Group "TTT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\ttt\ttt.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\ttt\ttt.h
# End Source File
# End Group
# Begin Group "NDS_Loader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\arm9\NDS_Loader\nds_loader.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\NDS_Loader\nds_loader.h
# End Source File
# Begin Source File

SOURCE=.\arm9\NDS_Loader\ndsload.h
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

SOURCE=.\arm9\main.cpp
# End Source File
# Begin Source File

SOURCE=.\arm9\main.h
# End Source File
# Begin Source File

SOURCE=.\arm9\Makefile
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
# Begin Group "_DarkStar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsBlank.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsBlank.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsClickable.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsClickable.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsEnums.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsGfx.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsGfx.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsInput.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsInput.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsSound.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsSound.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsSprite.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsSprite.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsSpriteEnum.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\dsSpriteManager.cpp
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsSpriteManager.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\dsSwapScreens.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\lib\DarkStar\huffman.c
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\huffman.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\vArray.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\vList.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\vName.h
# End Source File
# Begin Source File

SOURCE=..\ndslib\include\NDS\DarkStar\vTypes.h
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
# Begin Source File

SOURCE=".\vBase SDK License.txt"
# End Source File
# End Target
# End Project
