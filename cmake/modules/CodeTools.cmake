include(ClangFormat)

set(BEAUTIFICATION_TARGETS GLDemoPlatform)


# Defines new target for 'clangformat' to beautify whole project.
# Use 'make clangformat' or 'cmake --build . --target clangformat' to beautify the code.
# Beautification settings are located in .clang-format in project directory.

function(project_clangformat_setup)
    set(all_sources)
    set(beautification_dirs
            ${CMAKE_CURRENT_LIST_DIR}/Glitter/Sources
            ${CMAKE_CURRENT_LIST_DIR}/tests
            ${CMAKE_CURRENT_LIST_DIR}/v1)
    foreach( dir ${beautification_dirs} )
        file(GLOB_RECURSE TEMP_FILES ${dir}/*.mm ${dir}/*.m ${dir}/*.cpp ${dir}/*.h ${dir}/*.hpp)
        list(APPEND all_sources ${TEMP_FILES})
    endforeach()
    clangformat_setup(${all_sources})

    foreach(target ${BEAUTIFICATION_TARGETS})
        add_dependencies(${target} clangformat)
    endforeach()
endfunction()


function(project_codetools_setup)
    project_clangformat_setup()
endfunction()
