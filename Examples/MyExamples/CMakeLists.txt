add_executable(BlackScholesExample BlackScholesExample.cpp)
add_executable(AmericanOptionExample AmericanOptionExample.cpp)

target_link_libraries(BlackScholesExample ql_library ${QL_THREAD_LIBRARIES})
target_link_libraries(AmericanOptionExample ql_library ${QL_THREAD_LIBRARIES})

if (QL_INSTALL_EXAMPLES)
	install(TARGETS	BlackScholesExample RUNTIME DESTINATION ${QL_INSTALL_EXAMPLESDIR})
	install(TARGETS AmericanOptionExample RUNTIME DESTINATION ${QL_INSTALL_EXAMPLESDIR})
endif()
