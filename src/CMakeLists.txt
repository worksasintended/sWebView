# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

project ("slurm_gui")

SET (CMAKE_BUILD_TYPE DEBUG)
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
SET( CMAKE_EXPORT_COMPILE_COMMANDS on )

# Other Libraries
find_package( Boost COMPONENTS system thread signals)
find_library( wt wt )
find_library( wthttp wthttp )

add_executable( slurm_gui
  main.cpp
  AuthWidget.cpp
  InfoWidget.cpp
  RootApplication.cpp
  AdminWidget.cpp
  model/Session.cpp 
  model/User.cpp
)

target_link_libraries( slurm_gui wt wthttp wtdbosqlite3 wtdbo ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY} )

