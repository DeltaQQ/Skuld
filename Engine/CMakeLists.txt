project(Engine)

add_library(${PROJECT_NAME} STATIC
    "Source/Window/Window.h"
    "Source/Window/Window.cpp"
    "Source/Network/Common.h"
    "Source/Network/Message.h"
    "Source/Network/Client.h"
    "Source/Network/Server.h"
    "Source/Network/Connection.h"
    "Source/Data Structures/tsqueue.h"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS YES
    LINKER_LANGUAGE CXX

    ARCHIVE_OUTPUT_DIRECTORY "../Lib"
    # MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "Source"
    "C:/SDK/asio-1.22.1/include"
    "../Libraries/GLFW/include"
    "../Libraries/json"
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "../Libraries/GLFW/build/src/$<CONFIG>"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw3
)
