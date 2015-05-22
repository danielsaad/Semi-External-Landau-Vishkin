add_executable(example example.cpp)
target_link_libraries(example lvlib divsufsort pthread)
install(TARGETS example RUNTIME DESTINATION bin)