project(synth)
set(CMAKE_CXX_STANDARD 17)

if(LINUX)

  set(PLATFORM_LIBS stdc++fs asound)

endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} ${PLATFORM_LIBS})