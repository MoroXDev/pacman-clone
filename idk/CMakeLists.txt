# cmake_minimum_required (VERSION 3.8)

# project ("pac-man" CXX)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON) 

 
# file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
# file(GLOB_RECURSE sdl_libs CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/SDL/lib/*.a)
# file(GLOB_RECURSE sdl_image_libs CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/SDL_IMAGE/*.a)

# # set(sdl_mixer_lib ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)

# add_executable (${PROJECT_NAME} ${sources})

# target_link_libraries(${PROJECT_NAME} PRIVATE ${sdl_libs} ${sdl_image_libs})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_TTF/libSDL2_ttf.a)

# # target_link_libraries(${PROJECT_NAME} PRIVATE Winmm)
# # target_link_libraries(${PROJECT_NAME} PRIVATE Rpcrt4)
# # target_link_libraries(${PROJECT_NAME} )

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL/include/SDL2)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_IMAGE)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_TTF)




# target_include_directories(${PROJECT_NAME} PRIVATE "D:/msys64/clang64/include")

# cmake_minimum_required(VERSION 3.8)
# project(pac-man CXX)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

# add_executable(${PROJECT_NAME} ${sources})

# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_SOURCE_DIR}/src
#     ${CMAKE_SOURCE_DIR}/SDL/include/SDL2
#     ${CMAKE_SOURCE_DIR}/SDL_IMAGE
#     ${CMAKE_SOURCE_DIR}/SDL_MIXER
#     ${CMAKE_SOURCE_DIR}/SDL_TTF
# )

# # Dodaj folder z bibliotekami
# link_directories(${CMAKE_SOURCE_DIR}/SDL/lib)
# link_directories(${CMAKE_SOURCE_DIR}/SDL_IMAGE)
# link_directories(${CMAKE_SOURCE_DIR}/SDL_MIXER)
# link_directories(${CMAKE_SOURCE_DIR}/SDL_TTF)

# # Linkuj w tej kolejności i z użyciem nazw bez lib i rozszerzeń
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     mingw32
#     SDL2main
#     SDL2
#     SDL2_test
#     SDL2_image
#     SDL2_mixer
#     SDL2_ttf
#     -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
# )

# # set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
# # set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

cmake_minimum_required (VERSION 3.8)

project ("pac-man" CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

 
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

# set(sdl_mixer_lib ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable (${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL_MIXER_LIBRARIES SDL2::SDL_TTF_LIBRARIES SDL2::SDL_LIBRARIES SDL2::SDL_IMAGE_LIBRARIES)

# target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER/libSDL2_mixer.a)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_TTF/libSDL2_ttf.a)

# target_link_libraries(${PROJECT_NAME} PRIVATE Winmm)
# target_link_libraries(${PROJECT_NAME} PRIVATE Rpcrt4)
# target_link_libraries(${PROJECT_NAME} )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} SDLIMAGE_INCLUDE_DIR SDL_INCLUDE_DIRS SDLTTF_INCLUDE_DIR SDL_MIXER_INCLUDE_DIRS)

# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL/include/SDL2)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_IMAGE)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_MIXER)
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/SDL_TTF)