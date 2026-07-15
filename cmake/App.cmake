function(add_app NAME)
  file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  )
  add_executable(${NAME} ${SOURCES})

  setup_compiler(${NAME})

  set_target_properties(${NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin/${NAME} 
  )

  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/assets)
    add_custom_command(TARGET ${NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/bin/${NAME}/assets
    )
  endif()

  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(${NAME} PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/include")
  endif()

endfunction()