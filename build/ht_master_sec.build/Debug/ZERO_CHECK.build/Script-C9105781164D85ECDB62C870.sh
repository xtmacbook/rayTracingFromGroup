#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build
  make -f /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build
  make -f /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build
  make -f /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build
  make -f /Users/xtdoudou/Documents/workspace/ray-tracing-from-the-ground-up/build/CMakeScripts/ReRunCMake.make
fi

