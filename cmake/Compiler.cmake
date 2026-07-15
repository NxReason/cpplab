function(setup_compiler NAME)
  if (MSVC)
    target_compile_options(${NAME} PRIVATE
      /W4
      /permissive-
    )
  else()
    target_compile_options(${NAME} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
    )
  endif()

  target_compile_features(${NAME} PRIVATE
    cxx_std_23
  )

endfunction()