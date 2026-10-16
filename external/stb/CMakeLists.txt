add_library(stb STATIC
  src/stb_image.cpp
  src/stb_image_write.cpp)

target_include_directories(stb PUBLIC
  include)