Windows 8 App Build Process
___________________________


1) Install Visual Studio Express 2013

2) Install Microsoft Visual Studio 2012 Platform Toolset: I installed the whole thing  http://download.microsoft.com/download/D/4/8/D48D1AC2-A297-4C9E-A9D0-A218E6609F06/VSU4/VS2012.4.exe

3) clone the cordova-cef repo fork I created (private Github repo): https://github.com/magnan/cordova-cef.git 

4) There are two missing dependencies to fulfill:

    A) Install the a CEF binary distribution in 3rdparty/cef3. I used version: https://cefbuilds.s3.amazonaws.com/trunk/win/34.0.1846.251746/cef_binary_3.1846.1637_windows32_client.7z?Expires=1395357417&AWSAccessKeyId=AKIAJABJD5BP3O7W5E4A&Signature=rWom%2BfulOt%2BD4e%2Bd3CoE1ZKwEpQ%3D

    B) Install and compile Boost libraries in  3rdparty/boost : I used http://iweb.dl.sourceforge.net/project/boost/boost-binaries/1.55.0-build2/boost_1_55_0-msvc-8.0-32.exe
		

5) Open the main Visual Studio Project: windows-desktop.sln. Don’t upgrade the Platform Toolset to 2013 you need the 2012 Toolset to build. Try to build the Sentio product. If you can build and it launches in full screen then you completed a crucial step. 

6) Install node.js 

7) Learn about cordova at https://cordova.apache.org


