cmake_minimum_required(VERSION 3.18)

project(TerminalJobSearch LANGUAGES CXX)

option( "Use ASAN" FALSE)

set(TARGET_NAME TerminalJobSearch)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES
  ${SOURCE_DIR}/core.hpp        ${SOURCE_DIR}/core.cpp
  ${SOURCE_DIR}/companieDB.hpp  ${SOURCE_DIR}/companieDB.cpp
  ${SOURCE_DIR}/custom_table.h  ${SOURCE_DIR}/custom_table.cpp
  ${SOURCE_DIR}/main.cpp
)

add_executable(${TARGET_NAME}
    ${SOURCE_FILES}
)


target_include_directories(${TARGET_NAME} PUBLIC
    ${SOURCE_DIR}
)

if(USE_ASAN)
    if(WIN32)
        target_compile_options(${TARGET_NAME} PUBLIC /fsanitize=address)
        target_link_options(${TARGET_NAME} PUBLIC /fsanitize=address)
    else()
        target_compile_options(${TARGET_NAME} PUBLIC -fsanitize=address)
        target_link_options(${TARGET_NAME} PUBLIC -fsanitize=address)
    endif()
endif()

# enable c++23 features
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_23)
set_property(TARGET ${TARGET_NAME} PROPERTY
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE
)

# compile at max warning level + treat warnings as errors
target_compile_options(${TARGET_NAME} PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /MP>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)


# include(GNUInstallDirs)
# install(TARGETS TerminalJobSearch
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/SQLiteCpp)


target_link_libraries(${TARGET_NAME} PRIVATE
    # SQLiteCPP
    SQLiteCpp
    sqlite3
    pthread
    dl

    # Chose a submodule
    ftxui::component
    ftxui::dom
    ftxui::screen
)
