cmake_minimum_required(VERSION 3.26)
project(open_audio_engine)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fexec-charset=gbk)

set(src
 "api.cpp"
 "mono_data.cpp"
 "stereo_data.cpp"
 "mono_track.cpp"
 "stereo_track.cpp"
 "editor.cpp"
 "locker.cpp"
 "playback.cpp")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(open_audio_engine main.cpp ${src})
else()
    add_library(open_audio_engine SHARED ${src})
endif()

set_target_properties(open_audio_engine PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(open_audio_engine PRIVATE EXPORTED_FUNCTION_VISIBILITY=1)