set(PROJECT_NAME TribeTogether-Server)

################################################################################
# Source groups
################################################################################
set(Headers
    "Source/HeadlessConsole.h"
    "Source/ServerLayer.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "Source/CubedApp.cpp"
    "Source/HeadlessConsole.cpp"
    "Source/ServerLayer.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-fpermissive)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "App")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE TribeTogether-Server)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "TribeTogether-Server"
    TARGET_NAME_DIST    "TribeTogether-Server"
    TARGET_NAME_RELEASE "TribeTogether-Server"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/TribeTogether-Server/"
    OUTPUT_DIRECTORY_DIST    "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Dist-windows-x86_64/TribeTogether-Server/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/TribeTogether-Server/"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Dist>:
        MultiThreadedDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Dist>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../TribeTogether-Common/Source;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/vendor/glm;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/Walnut/Source;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/Walnut/Platform/Headless;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/vendor/spdlog/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/vendor/yaml-cpp/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/Walnut-Modules/Walnut-Networking/Source;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Walnut/Walnut-Modules/Walnut-Networking/vendor/GameNetworkingSockets/include"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "WL_DEBUG"
    ">"
    "$<$<CONFIG:Dist>:"
        "WL_DIST"
    ">"
    "$<$<CONFIG:Release>:"
        "WL_RELEASE"
    ">"
    "WL_HEADLESS;"
    "YAML_CPP_STATIC_DEFINE;"
    "WL_PLATFORM_WINDOWS;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI
        >
        $<$<CONFIG:Dist>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            /Zi
        >
        /W3;
        /EHsc;
        /Zc:preprocessor;
        /Zc:__cplusplus;
        /utf-8;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
        >
        $<$<CONFIG:Dist>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Release>:
            /DEBUG;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Post build events
################################################################################
add_custom_command_if(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMANDS
    COMMAND   $<CONFIG:Debug> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\GameNetworkingSockets.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\GameNetworkingSockets.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\GameNetworkingSockets.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND   $<CONFIG:Debug> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libcrypto-3-x64.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libcrypto-3-x64.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libcrypto-3-x64.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND   $<CONFIG:Debug> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libprotobufd.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libprotobufd.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Debug\\libprotobufd.dll" "..\\bin\\Debug-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND    $<CONFIG:Dist> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\GameNetworkingSockets.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\GameNetworkingSockets.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\GameNetworkingSockets.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND    $<CONFIG:Dist> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libcrypto-3-x64.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libcrypto-3-x64.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libcrypto-3-x64.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND    $<CONFIG:Dist> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libprotobufd.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libprotobufd.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Dist\\libprotobufd.dll" "..\\bin\\Dist-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND $<CONFIG:Release> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\GameNetworkingSockets.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\GameNetworkingSockets.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\GameNetworkingSockets.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND $<CONFIG:Release> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libcrypto-3-x64.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libcrypto-3-x64.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libcrypto-3-x64.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul)
    COMMAND $<CONFIG:Release> IF EXIST "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libprotobufd.dll"\\ (xcopy /Q /E /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libprotobufd.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul) ELSE (xcopy /Q /Y /I "..\\Walnut\\Walnut-Modules\\Walnut-Networking\\vendor\\GameNetworkingSockets\\bin\\windows\\Release\\libprotobufd.dll" "..\\bin\\Release-windows-x86_64\\TribeTogether-Server" > nul)
)

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
        TribeTogether-Common-Headless
        Walnut-Headless
        Walnut-Networking
        yaml-cpp
        ${CMAKE_SOURCE_DIR}/Walnut/Walnut-Modules/Walnut-Networking/vendor/GameNetworkingSockets/bin/Windows/Debug/GameNetworkingSockets.lib
)