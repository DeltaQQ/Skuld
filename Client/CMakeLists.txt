project(Client)

add_executable(${PROJECT_NAME}
    "Source/main.cpp"
    "Source/GameClient.h"
    "Source/GameClient.cpp"
    "Source/Authentication.h"
    "Source/Authentication.cpp"
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
    "../Server/Source"
    "C:/SDK/firebase_cpp_sdk/include"
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "C:/SDK/firebase_cpp_sdk/libs/windows/VS2019/MD/x64/$<CONFIG>"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Engine
    Crypt32
    firebase_auth
    firebase_app
)
