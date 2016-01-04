
set(include_lvlib_dir "${CMAKE_SOURCE_DIR}/include/lvlib")
add_library(lv STATIC  LandauVishkin.cpp RMQ.cpp text.cpp ${include_lvlib_dir}/Index.hpp ${include_lvlib_dir}/LandauVishkin.hpp
    ${include_lvlib_dir}/RMQ.hpp ${include_lvlib_dir}/text.hpp ${include_lvlib_dir}/types.hpp)
install(TARGETS lv ARCHIVE DESTINATION lib)
