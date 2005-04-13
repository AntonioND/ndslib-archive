
Example makefiles assume that you have NDSLIBPATH defined as a system variable as well as devkitarm/bin included in your path.  You can explicitly define these in each makefile if you choose.

The tools directory contains the tools required to build the .nds file (ndstool by darkfader www.darkfader.net/ds) and the tool that appends a loader to the nds file (dsbuild by dovoto which will hopefully soon be replaced by costis's loader).  There is also a tool by Natrium (www.natrium42.com) for building an icon.  My loader does not display any graphics so at the moment including your own icon is sort of pointless.

Examples expect source files to be in the source directory and include files to be in an include directory.  Data and graphics can be put in the data directory and will automagicaly be included in your project if they have a file extension of:

pcx, bin, raw or pal.  

You can access then via the automaticaly created header file filename.h   (see some examples if this is unclear).


Make produces a .nds file for emulator use (dualis is the only one that curently supports this) as well as a .nds.gba file for flashing to your gba flash cart and running with your passme.  Intermediate files get stored in the build directory and the arm9.bin can be found in here.




In windows:

To add a system variable just right click on "my computer" then properties then "advanced tab".  click "environment variables".  Find PATH in your user variable list and edit it to include a path to your devkit bin directory. 

Next click "new" under system variables and make a new variable called NDSLIBPATH.  set it equal to the path to your ndslib directory.  For me it is:


c:/dev/ds/ndslib

notice the "unix" style slashes.

assuming you have minsys installed and in your path the examples should build.  