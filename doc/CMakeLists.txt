OPTION( BUILD_DOCUMENTATION "If on doxygen documentation will be generated" ON)

IF( BUILD_DOCUMENTATION )

  function(JOIN VALUES GLUE OUTPUT)
    string (REPLACE ";" "${GLUE}" _TMP_STR "${VALUES}")
    set (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
  endfunction()

  FIND_PACKAGE(Doxygen 1.8.3 REQUIRED)
  
  SET( doxyfile_in          ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in     )
  SET( doxyfile             ${PROJECT_BINARY_DIR}/Doxyfile              )
  SET( doxy_html_index_file ${CMAKE_CURRENT_BINARY_DIR}/html/index.html )
  SET( doxy_output_root     ${CMAKE_CURRENT_BINARY_DIR}                 ) # Pasted into Doxyfile.in
  SET( doxy_input           ${PROJECT_SOURCE_DIR}/src
                            ${PROJECT_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/include/impl          ) # Pasted into Doxyfile.in
  SET( doxy_extra_files     ${CMAKE_CURRENT_SOURCE_DIR}/mainpage.dox    ) # Pasted into Doxyfile.in
  
  # Fix value lists before substitution...
  JOIN("${doxy_input}" " " doxy_input)
  CONFIGURE_FILE( ${doxyfile_in} ${doxyfile} @ONLY )
 
  ADD_CUSTOM_COMMAND( OUTPUT ${doxy_html_index_file}
                      COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                      # The following should be ${doxyfile} only but it will break the dependency.
                      # The optimal solution would be creating a custom_command for ${doxyfile}
                      # generation but I still have to figure out how...
                      MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
                      DEPENDS ${doxy_extra_files}
                      COMMENT "Generating HTML documentation")
  
  ADD_CUSTOM_TARGET( doc ALL DEPENDS ${doxy_html_index_file} ${SeismicTraces_includes} )
  
  INSTALL( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc )  

ENDIF()
