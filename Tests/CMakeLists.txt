project(Tests)

add_executable(${PROJECT_NAME}
    "Source/main.cpp"
    "Source/Engine/Network/TestMessage.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
    LINKER_LANGUAGE CXX

    RUNTIME_OUTPUT_DIRECTORY "../Bin"
    # MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "../Libraries/Catch2"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Engine
)