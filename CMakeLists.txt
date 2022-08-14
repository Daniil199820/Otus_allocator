cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VERSION})

add_executable(allocator main.cpp)
add_executable(lib_allocators lib_allocators.h)
add_executable(lib_containers lib_containers.h)

set_target_properties(allocator lib_allocators lib_containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_directories(allocator PRIVATE
lib_allocators
lib_containers
)

#target_include_directories(allocator PRIVATE
 #   lib_allocators
 #   lib_containers
#)

if (MSVC)

    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(lib_allocators PRIVATE
        /W4
    )
    target_compile_options(lib_containers PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_allocators PRIVATE
    -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_containers PRIVATE
    -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)