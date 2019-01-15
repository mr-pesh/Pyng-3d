macro(list_subdirectories RESULT_LIST CURRENT_DIR)
    file(GLOB CHILDREN RELATIVE ${CURRENT_DIR} ${CURRENT_DIR}/*)

    set(DIR_LIST "")

    foreach(CHILD ${CHILDREN})
        if(IS_DIRECTORY ${CURRENT_DIR}/${CHILD})
            list(APPEND DIR_LIST ${CHILD})
        endif()
    endforeach()

    set(${RESULT_LIST} ${DIR_LIST})
endmacro()
