workspace "TribeTogether-Client"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "TribeTogether-Client"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

   defines { "IMGUI_DEFINE_MATH_OPERATORS" }

-- Directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
WalnutNetworkingBinDir = "Walnut/Walnut-Modules/Walnut-Networking/vendor/GameNetworkingSockets/bin/%{cfg.system}/%{cfg.buildcfg}/"

include "Walnut/Build-Walnut-External.lua"

group "App"
    include "TribeTogether-Common/Build-TribeTogether-Common.lua"
    include "TribeTogether-Client/Build-TribeTogether-Client.lua"
group ""