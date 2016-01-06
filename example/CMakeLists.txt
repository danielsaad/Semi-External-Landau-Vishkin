add_executable(example example.cpp)
target_link_libraries(example lib_lv lib_divsufsort lib_divsufsort64 pthread)
install(TARGETS example RUNTIME DESTINATION bin)
