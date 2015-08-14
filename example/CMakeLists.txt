add_executable(example example.cpp)
target_link_libraries(example lv divsufsort pthread)
install(TARGETS example RUNTIME DESTINATION bin)