FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/schunk_sdh/msg"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/TactileSensor.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_TactileSensor.lisp"
  "../msg_gen/lisp/TactileMatrix.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_TactileMatrix.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
