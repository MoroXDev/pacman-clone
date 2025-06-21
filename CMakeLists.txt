cmake_minimum_required (VERSION 3.8)

project ("pac-man" CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

 
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE sdl_libs CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/SDL/lib/x64/*.lib)
file(GLOB_RECURSE sdl_image_libs CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/SDL_IMAGE/*.a)

# set(sdl_mixer_lib ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)

add_executable (${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} PRIVATE ${sdl_libs} ${sdl_image_libs})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)
target_link_libraries(${PROJECT_NAME} PRIVATE Winmm)
# target_link_libraries(${PROJECT_NAME} )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL/include/SDL2)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_IMAGE)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER)