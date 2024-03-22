#! /bin/sh

# *my* cert
export DEVID="Developer ID Application"

# *my* Depot Tools path
export PATH=/Volumes/Work/Tools/DepotTools:$PATH

# *my* HelloWebGPU path
export HELLO_WEBGPU_MAC=../hello-webgpu/lib/dawn/bin/mac/

# All the target paths
export DAWN_OUT_DBG_ARM=out/dbg-arm
export DAWN_OUT_DBG_X64=out/dbg-x64
export DAWN_OUT_REL_ARM=out/rel-arm
export DAWN_OUT_REL_X64=out/rel-x64

# Note: use_custom_libcxx=false didn't work on Mac due to macro redefinition (needs investigation)

# Common flags
export DAWN_COMMON="use_partition_alloc=false use_custom_libcxx=false"

# Debug but reduced in size
export DAWN_DBG_SMALL="is_debug=true strip_debug_info=true enable_stripping=true symbol_level=0 enable_iterator_debugging=false"

# Release with optimisations
export DAWN_REL_SMALL="is_official_build=true chrome_pgo_phase=false"

# No Vulkan (or anything else) only Metal
export DAWN_USE_METAL="dawn_enable_vulkan=false dawn_use_swiftshader=false"

cd /Volumes/Work/Native/Dawn
