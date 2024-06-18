add_executable(EquityOption EquityOption.cpp)
add_executable(EquityOptionTH EquityOptionTH.cpp)

target_link_libraries(EquityOption ql_library ${QL_THREAD_LIBRARIES})
target_link_libraries(EquityOptionTH ql_library ${QL_THREAD_LIBRARIES})

if (QL_INSTALL_EXAMPLES)
    install(TARGETS EquityOption RUNTIME DESTINATION ${QL_INSTALL_EXAMPLESDIR})
    install(TARGETS EquityOptionTH RUNTIME DESTINATION ${QL_INSTALL_EXAMPLESDIR})
endif()
