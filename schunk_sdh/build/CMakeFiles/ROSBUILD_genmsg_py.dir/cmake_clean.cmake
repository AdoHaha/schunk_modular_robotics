FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/schunk_sdh/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/schunk_sdh/msg/__init__.py"
  "../src/schunk_sdh/msg/_TactileSensor.py"
  "../src/schunk_sdh/msg/_TactileMatrix.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
