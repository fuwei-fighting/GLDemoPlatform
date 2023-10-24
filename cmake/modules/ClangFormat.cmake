function(clangformat_setup)
  if(NOT CLANGFORMAT_EXECUTABLE)
    set(CLANGFORMAT_EXECUTABLE  ${CMAKE_CURRENT_LIST_DIR}/tools/clang-format)
  endif()

  if(NOT EXISTS ${CLANGFORMAT_EXECUTABLE})
    find_program(clangformat_executable_tmp ${CLANGFORMAT_EXECUTABLE})
    if(clangformat_executable_tmp)
      set(CLANGFORMAT_EXECUTABLE ${clangformat_executable_tmp})
      unset(clangformat_executable_tmp)
    else()
      message(ERROR "ClangFormat: ${CLANGFORMAT_EXECUTABLE} not found! Aborting")
      return()
    endif()
  endif()

  foreach(clangformat_source ${ARGV})
    get_filename_component(clangformat_source ${clangformat_source} ABSOLUTE)
    if (EXISTS ${clangformat_source} AND ${clangformat_source} MATCHES ".+\\.(cc|h|mm|m|hpp|cpp|c)$")
      list(APPEND clangformat_sources ${clangformat_source})
    endif()
  endforeach()

  add_custom_target(${PROJECT_NAME}_clangformat
    COMMAND
      ${CLANGFORMAT_EXECUTABLE}
      -style=file
      -i
      ${clangformat_sources}
    COMMENT
      "Formating with ${CLANGFORMAT_EXECUTABLE} ..."
  )

  if(TARGET clangformat)
    add_dependencies(clangformat ${PROJECT_NAME}_clangformat)
  else()
    add_custom_target(clangformat DEPENDS ${PROJECT_NAME}_clangformat)
  endif()
endfunction()

function(target_clangformat_setup target)
  get_target_property(target_sources ${target} SOURCES)
  clangformat_setup(${target_sources})
endfunction()
