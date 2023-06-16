cmake_minimum_required(VERSION 3.15)
project(OSCreciever)

add_subdirectory(JUCE)
add_subdirectory(JuceLibraryCode)

include_directories(/usr/local/lib/onnxruntime-linux-x64-1.15.0/include)

juce_add_plugin(OSCrecieverPlugin
    VERSION 1.0.0                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    # COMPANY_NAME ...                          # Specify the name of the plugin's author
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
    NEEDS_MIDI_INPUT TRUE                       # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT TRUE                      # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE                # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Oscr                            # A unique four-character plugin id with exactly one upper-case character
                                                # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "OSCreciever")                 # The name of the final executable, which can differ from the target name

juce_generate_juce_header(OSCrecieverPlugin)

target_sources(OSCrecieverPlugin
    PRIVATE        
        JuceLibraryCode/include_juce_audio_basics.cpp
        JuceLibraryCode/include_juce_audio_devices.cpp
        JuceLibraryCode/include_juce_audio_formats.cpp
        JuceLibraryCode/include_juce_audio_plugin_client_ARA.cpp
        JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
        JuceLibraryCode/include_juce_audio_processors.cpp
        JuceLibraryCode/include_juce_audio_processors_lv2_libs.cpp
        JuceLibraryCode/include_juce_audio_utils.cpp
        JuceLibraryCode/include_juce_core.cpp
        JuceLibraryCode/include_juce_data_structures.cpp
        JuceLibraryCode/include_juce_events.cpp
        JuceLibraryCode/include_juce_graphics.cpp
        JuceLibraryCode/include_juce_gui_basics.cpp
        JuceLibraryCode/include_juce_gui_extra.cpp
        JuceLibraryCode/include_juce_osc.cpp

        PluginEditor.cpp
        PluginProcessor.cpp
)

target_compile_definitions(OSCrecieverPlugin
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(AudioPluginData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

target_link_libraries(OSCrecieverPlugin
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
        juce::juce_osc
        ${LIB_NAME} /usr/local/lib/onnxruntime-linux-x64-1.15.0/lib/libonnxruntime.so.1.15.0
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)