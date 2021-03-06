# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

project ("slurm_gui")

SET (CMAKE_BUILD_TYPE DEBUG)
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -g -fno-omit-frame-pointer" )
SET( CMAKE_EXPORT_COMPILE_COMMANDS on )

option( debug_login "deactivate login for debugging" on )
option( enable_registration "enable registration of accounts" off )

if ( debug_login ) 
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_DEBUG_BUILD=1 " )
endif()

if ( enable_registration )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_REGISTRATION=1 " )
endif()


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
  PartitionsInfo.cpp
  PartitionInfo.cpp
  NodesInfo.cpp
  NodeInfo.cpp
  ReservationsInfo.cpp
  ReservationInfo.cpp
  UsersInfo.cpp 
  UsersInfoWidget.cpp 
  UserInfo.cpp
  ClusterInfo.cpp
  ClustersInfo.cpp
  AccountInfo.cpp 
  AccountsInfo.cpp 
  AccountsInfoWidget.cpp 
  AssociationInfo.cpp 
  JobsInfoWidget.cpp
  JobsInfo.cpp
  JobInfo.cpp
  SlurmDB.cpp
  ReservationsInfoWidget.cpp
  model/Session.cpp 
  model/User.cpp
)

target_link_libraries( slurm_gui wt wthttp wtdbosqlite3 wtdbo slurm slurmdb ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SIGNALS_LIBRARY} )


add_subdirectory( test )
