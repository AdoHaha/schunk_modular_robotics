FILE(REMOVE_RECURSE
  "../msg_gen"
  "../src/schunk_sdh/msg"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/schunk_sdh/TactileMatrix.h"
  "../msg_gen/cpp/include/schunk_sdh/TactileSensor.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
