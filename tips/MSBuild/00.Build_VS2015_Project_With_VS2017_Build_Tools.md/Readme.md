# Build VS2015 Project with VS2017 Build Tools

* Use MSBuild from VS2017 Build Tools to build VS2015 project, will Failed  
  ![Default build failed](DefaultBuildFailed.png)

* Find the installed platform toolset and build again with it  
  ![Installed Platform Toolset Path](GetListOfInstalledPlatformToolsets.png)  
  Build again with the correct platfom toolset  
  ![Build failed again](BuildFailedAgainWithCorrectPlatformToolset.png)  
  We could see that it failed again, but failed at not correct SDK

* Find the installed Windows SDK  
  ![Find the installed SDK](InstalledSDK.png)  
  Build with correct Toolset and SDK  
  ![](BuildSuccess_01.png)  
  ![](BuildSuccess_02.png)  
  ![](BuildSuccess_03.png)  