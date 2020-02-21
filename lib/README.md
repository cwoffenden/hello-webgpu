Dawn build instructions:

1. VisualStudio (VS2015/17/19). Community edition is fine. Make sure the CMake option is enabled.

2. You need the the full Windows 10 SDK; VS will install the Win10 SDK from VS (via the VS Installer) but it misses the required "Debugging Tools for Windows":

	https://developer.microsoft.com/en-gb/windows/downloads/windows-10-sdk/

3. Up-to-date graphics drivers and the Vulkan SDK:

	https://www.lunarg.com/vulkan-sdk/

4. Git. I have Git for Windows installed along with the MS Credential Manager:
		
	https://github.com/Microsoft/Git-Credential-Manager-for-Windows/releases/tag/1.20.0
		
5. Google's Depot Tools:

	http://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up
	
I didn't install Depot Tools the recommended way, instead I did this:

	5.1 Make sure Git is on the PATH (via the environment variable control panel)
	
	5.1 Launch a VS2019 x64 Native Tools Command Prompt
	
	5.2 Set-up Git following the "Bootstrapping" section in the Depot Tools page above
	
	5.3 cd into your dev/work/code directory (mine is C:\Volumes\Data\Work\Native)
	
	5.4 git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
	
	5.5 Add Depot Tools to the front of your PATH in the current Command Prompt:
	
		set PATH=C:\Volumes\Data\Work\Native\depot_tools;%PATH%
	
	5.6 Run 'gclient' (which should download the CIPD client then show you some options)

	5.7 Add win32file to Depot Tools' Python (verify with 'where python' that Depot Tools is the correct python executable):

		python -m pip install pywin32
	
The reason for doing it this way is it keeps the random self-updating Depot Tools from being the first PATH entry (and the Google instructions are a bit clunky for Windows).

6. In the same VS2019 x64 Prompt above, with the same PATH, etc., clone Dawn following the Building Dawn instructions:

	https://dawn.googlesource.com/dawn/+/HEAD/docs/buiding.md

The copy needs making Windows friendly and the local VS toolchain needs enabling:

	git clone https://dawn.googlesource.com/dawn dawn && cd dawn
	
	copy scripts\standalone.gclient .gclient
	
	set DEPOT_TOOLS_WIN_TOOLCHAIN=0
	
	gclient sync
	
7. Configure then build Dawn:

	5.1 gn args out/Release
	
	5.2 In the text file that opened add "is_debug=false", save then close it
	
	5.3 ninja -C out\Release
	
8. That should be it. Run the samples in the build directory. Now that the basic install can build and run, the configuration can be investigated and tweaked:

	gn args out/Release --list

For release I went with:

is_clang=false
is_debug=false
strip_debug_info=true
symbol_level=0
asan_globals=false

is_clang=false
is_debug=true
enable_iterator_debugging=true (note: build with _ITERATOR_DEBUG_LEVEL=0 if setting this to false)

With builds for both target_cpu="x64" and target_cpu="x86".

Command line warning D9002 : ignoring unknown option '/Zc:twoPhase'
	
9. Pretty much the same steps are needed to build ANGLE:

	https://chromium.googlesource.com/angle/angle/+/HEAD/doc/DevSetup.md

With same arguments as Dawn plus:

angle_enable_swiftshader=false
angle_enable_vulkan=false

Note: ANGLE currently fails to build when disabling D3D9.
