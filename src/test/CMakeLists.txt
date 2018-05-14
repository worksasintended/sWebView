enable_testing()

add_executable( bin_slurm_db_test slurm_db_test.cpp ${CMAKE_SOURCE_DIR}/SlurmDB.cpp) 
target_include_directories(bin_slurm_db_test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(bin_slurm_db_test PRIVATE slurmdb slurm )

add_executable( bin_users_info_test users_info_test.cpp ${CMAKE_SOURCE_DIR}/SlurmDB.cpp ${CMAKE_SOURCE_DIR}/AssociationInfo.cpp ${CMAKE_SOURCE_DIR}/UsersInfo.cpp ${CMAKE_SOURCE_DIR}/UserInfo.cpp ) 
target_include_directories(bin_users_info_test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(bin_users_info_test PRIVATE slurmdb slurm )

