add_library(lv STATIC  LandauVishkin.cpp RMQ.cpp text.cpp)
install(TARGETS lv ARCHIVE DESTINATION lib)
