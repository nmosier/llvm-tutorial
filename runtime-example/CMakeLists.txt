llvm_add_library(TracePass SHARED CallbackPass.cpp)

add_library(TraceRuntime STATIC TraceRuntime.c)

add_executable(test test.c)
set_source_files_properties(test.c PROPERTIES OBJECT_DEPENDS TracePass)
target_compile_options(test PRIVATE -flegacy-pass-manager "SHELL:-Xclang -load" "SHELL:-Xclang $<TARGET_FILE:TracePass>")
target_link_libraries(test PRIVATE TraceRuntime)
