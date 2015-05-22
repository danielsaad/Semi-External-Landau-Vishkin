add_library(lvlib STATIC  LandauVishkin.cpp RMQ.cpp text.cpp)

install(TARGETS lvlib ARCHIVE DESTINATION lib)