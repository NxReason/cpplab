add_app(hello_world)

target_link_libraries(hello_world
  PRIVATE
    cli_output
    common
)