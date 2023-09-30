add_executable(main 
    ./cpp/main.cpp 
    ./cpp/Bird.cpp 
    ./cpp/FlappyBird.cpp
    ./cpp/GameObject.cpp
    ./cpp/PhisicalObject.cpp
    ./cpp/SGameEngine.cpp
)

set(MY_SFML_PATH D:\\Development\\Libs\\SFML-2.6.0\\lib\\cmake\\SFML)
set(SFML_DIR ${MY_SFML_PATH})
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)
target_include_directories(main PRIVATE ./hdr)

install(DIRECTORY sprites
        CONFIGURATIONS Debug
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/flappy-bird
)

install(DIRECTORY sprites
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/flappy-bird
)

install(TARGETS main
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/flappy-bird
)

install(TARGETS main
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/flappy-bird
)