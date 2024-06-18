add_executable(BlackScholesExample BlackScholesExample.cpp)
# add_executable(BlackKarasinskiExample BlackKarasinskiExample.cpp)
add_executable(BlackVasicekExample BlackVasicekExample.cpp)

target_link_libraries(BlackScholesExample ql_library ${QL_THREAD_LIBRARIES})
# target_link_libraries(BlackKarasinskiExample ql_library ${QL_THREAD_LIBRARIES})
target_link_libraries(BlackVasicekExample ql_library ${QL_THREAD_LIBRARIES})

if (QL_INSTALL_EXAMPLES)
	install(TARGETS	BlackScholesExample RUNTIME DESTINATION ${QL_INSTALL_EXAMPLESDIR})
endif()
