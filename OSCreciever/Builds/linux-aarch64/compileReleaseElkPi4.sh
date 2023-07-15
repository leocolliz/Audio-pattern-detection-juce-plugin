#!/bin/bash
# Cross-compilation script for ElkOS on RPI4
# Instructions at:
# https://elk-audio.github.io/elk-docs/html/documents/building_plugins_for_elk.html#cross-compiling-juce-plugin

unset LD_LIBRARY_PATH
source /opt/elk/0.11.0/environment-setup-cortexa72-elk-linux
export CXXFLAGS="-O3 -pipe -ffast-math -feliminate-unused-debug-types -funroll-loops -Wno-poison-system-directories"
AR=aarch64-elk-linux-ar make -j`nproc` CONFIG=Release CFLAGS="-DJUCE_HEADLESS_PLUGIN_CLIENT=1 -Wno-psabi" TARGET_ARCH="-mcpu=cortex-a72 -mtune=cortex-a72"
# Rename VST3 inner path to match the subfolder expexted by elkos
for f in `find build -name "*.vst3"`; do mv $f/Contents/arm64-linux $f/Contents/aarch64-linux; done
