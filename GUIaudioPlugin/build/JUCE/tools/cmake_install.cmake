# Install script for directory: /home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/extras/Build/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/JUCEConfigVersion.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/JUCEConfig.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/JUCEModuleSupport.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/JuceLV2Defines.h.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/copyDir.cmake"
    "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5" TYPE EXECUTABLE FILES "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/juce_lv2_helper")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5/juce_lv2_helper" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5/juce_lv2_helper")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/JUCE-7.0.5/juce_lv2_helper")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake"
         "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/CMakeFiles/Export/lib/cmake/JUCE-7.0.5/LV2_HELPER-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/leo/UNI/tirocinio/Audio-pattern-detection-juce-plugin/GUIaudioPlugin/build/JUCE/tools/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
