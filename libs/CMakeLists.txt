add_subdirectory(espdsp)
add_library(thirdparty INTERFACE)
target_link_libraries(thirdparty INTERFACE espdsp)
