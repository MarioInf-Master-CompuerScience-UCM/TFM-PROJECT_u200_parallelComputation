cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules")

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCL REQUIRED)
find_package(XRT REQUIRED)
find_package(OpenMP REQUIRED)
find_package(jsoncpp REQUIRED)


if(NOT XRT_FOUND)
  message(FATAL_ERROR "XRT not found, please source XRT setup script before building")
endif()

if(NOT TARGET OpenMP::OpenMP_CXX)
    find_package(Threads REQUIRED)
    add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
    set_property(TARGET OpenMP::OpenMP_CXX PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
    set_property(TARGET OpenMP::OpenMP_CXX PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} Threads::Threads)
endif()

#*********************************
# MACROS DEFINITION ZONE  - START*
#*********************************
macro(EXTRACT_KERNEL_FOLDER cadena_sin_procesar resultado)

    string(REPLACE "_" ";" PARTES_LISTA ${cadena_sin_procesar})
    list(LENGTH PARTES_LISTA PARTES_COUNT)

    if(PARTES_COUNT GREATER 2)
        list(GET PARTES_LISTA 1 PARTE2)
        list(GET PARTES_LISTA 2 PARTE3)        
        string(CONCAT ${resultado} "ker_" ${PARTE2} "_" ${PARTE3})

    else()
        set(${resultado} "")
        
    endif()

endmacro()
#*********************************
# MACROS DEFINITION ZONE  - END  *
#*********************************




#********************************
# COPIYING KERNEL FILES - START *
#********************************
set(kerPackList)
list(APPEND kerPackList "kerPack_vectorAdd_Opt0_mini" "kerPack_vectorAdd_Opt0_small" "kerPack_vectorAdd_Opt0_medium" "kerPack_vectorAdd_Opt0_large" "kerPack_vectorAdd_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_vectorAdd_Opt1_mini" "kerPack_vectorAdd_Opt1_small" "kerPack_vectorAdd_Opt1_medium" "kerPack_vectorAdd_Opt1_large" "kerPack_vectorAdd_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_vectorAdd_Opt2_mini" "kerPack_vectorAdd_Opt2_small" "kerPack_vectorAdd_Opt2_medium" "kerPack_vectorAdd_Opt2_large" "kerPack_vectorAdd_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_vectorAdd_Opt3_mini" "kerPack_vectorAdd_Opt3_small" "kerPack_vectorAdd_Opt3_medium" "kerPack_vectorAdd_Opt3_large" "kerPack_vectorAdd_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_vectorAdd_Opt4_mini" "kerPack_vectorAdd_Opt4_small" "kerPack_vectorAdd_Opt4_medium" "kerPack_vectorAdd_Opt4_large" "kerPack_vectorAdd_Opt4_extralarge" )

list(APPEND kerPackList "kerPack_studyCase1_a_mini" "kerPack_studyCase1_a_small" "kerPack_studyCase1_a_medium" "kerPack_studyCase1_a_large" "kerPack_studyCase1_a_extralarge" )
list(APPEND kerPackList "kerPack_studyCase1_b_mini" "kerPack_studyCase1_b_small" "kerPack_studyCase1_b_medium" "kerPack_studyCase1_b_large" "kerPack_studyCase1_b_extralarge" )
list(APPEND kerPackList "kerPack_studyCase1_c_mini" "kerPack_studyCase1_c_small" "kerPack_studyCase1_c_medium" "kerPack_studyCase1_c_large" "kerPack_studyCase1_c_extralarge" )

list(APPEND kerPackList "kerPack_studyCase2_a_mini" "kerPack_studyCase2_a_small" "kerPack_studyCase2_a_medium" "kerPack_studyCase2_a_large" "kerPack_studyCase2_a_extralarge" )
list(APPEND kerPackList "kerPack_studyCase2_b_mini" "kerPack_studyCase2_b_small" "kerPack_studyCase2_b_medium" "kerPack_studyCase2_b_large" "kerPack_studyCase2_b_extralarge" )
list(APPEND kerPackList "kerPack_studyCase2_c_mini" "kerPack_studyCase2_c_small" "kerPack_studyCase2_c_medium" "kerPack_studyCase2_c_large" "kerPack_studyCase2_c_extralarge" )
list(APPEND kerPackList "kerPack_studyCase2_d_mini" "kerPack_studyCase2_d_small" "kerPack_studyCase2_d_medium" "kerPack_studyCase2_d_large" "kerPack_studyCase2_d_extralarge" )

list(APPEND kerPackList "kerPack_studyCase3_a_mini" "kerPack_studyCase3_a_small" "kerPack_studyCase3_a_medium" "kerPack_studyCase3_a_large" "kerPack_studyCase3_a_extralarge" )
list(APPEND kerPackList "kerPack_studyCase3_b_mini" "kerPack_studyCase3_b_small" "kerPack_studyCase3_b_medium" "kerPack_studyCase3_b_large" "kerPack_studyCase3_b_extralarge" )
list(APPEND kerPackList "kerPack_studyCase3_c_mini" "kerPack_studyCase3_c_small" "kerPack_studyCase3_c_medium" "kerPack_studyCase3_c_large" "kerPack_studyCase3_c_extralarge" )
list(APPEND kerPackList "kerPack_studyCase3_d_mini" "kerPack_studyCase3_d_small" "kerPack_studyCase3_d_medium" "kerPack_studyCase3_d_large" "kerPack_studyCase3_d_extralarge" )

list(APPEND kerPackList "kerPack_cholesky_Opt0_mini" "kerPack_cholesky_Opt0_small" "kerPack_cholesky_Opt0_medium" "kerPack_cholesky_Opt0_large" "kerPack_cholesky_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_cholesky_Opt1_mini" "kerPack_cholesky_Opt1_small" "kerPack_cholesky_Opt1_medium" "kerPack_cholesky_Opt1_large" "kerPack_cholesky_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_cholesky_Opt2_mini" "kerPack_cholesky_Opt2_small" "kerPack_cholesky_Opt2_medium" "kerPack_cholesky_Opt2_large" "kerPack_cholesky_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_cholesky_Opt3_mini" "kerPack_cholesky_Opt3_small" "kerPack_cholesky_Opt3_medium" "kerPack_cholesky_Opt3_large" "kerPack_cholesky_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_cholesky_Opt4_mini" "kerPack_cholesky_Opt4_small" "kerPack_cholesky_Opt4_medium" "kerPack_cholesky_Opt4_large" "kerPack_cholesky_Opt4_extralarge" )

list(APPEND kerPackList "kerPack_doitgen_Opt0_mini" "kerPack_doitgen_Opt0_small" "kerPack_doitgen_Opt0_medium" "kerPack_doitgen_Opt0_large" "kerPack_doitgen_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_doitgen_Opt1_mini" "kerPack_doitgen_Opt1_small" "kerPack_doitgen_Opt1_medium" "kerPack_doitgen_Opt1_large" "kerPack_doitgen_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_doitgen_Opt2_mini" "kerPack_doitgen_Opt2_small" "kerPack_doitgen_Opt2_medium" "kerPack_doitgen_Opt2_large" "kerPack_doitgen_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_doitgen_Opt3_mini" "kerPack_doitgen_Opt3_small" "kerPack_doitgen_Opt3_medium" "kerPack_doitgen_Opt3_large" "kerPack_doitgen_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_doitgen_Opt4_mini" "kerPack_doitgen_Opt4_small" "kerPack_doitgen_Opt4_medium" "kerPack_doitgen_Opt4_large" "kerPack_doitgen_Opt4_extralarge" )

list(APPEND kerPackList "kerPack_gemm_Opt0_mini" "kerPack_gemm_Opt0_small" "kerPack_gemm_Opt0_medium" "kerPack_gemm_Opt0_large" "kerPack_gemm_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_gemm_Opt1_mini" "kerPack_gemm_Opt1_small" "kerPack_gemm_Opt1_medium" "kerPack_gemm_Opt1_large" "kerPack_gemm_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_gemm_Opt2_mini" "kerPack_gemm_Opt2_small" "kerPack_gemm_Opt2_medium" "kerPack_gemm_Opt2_large" "kerPack_gemm_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_gemm_Opt3_mini" "kerPack_gemm_Opt3_small" "kerPack_gemm_Opt3_medium" "kerPack_gemm_Opt3_large" "kerPack_gemm_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_gemm_Opt4_mini" "kerPack_gemm_Opt4_small" "kerPack_gemm_Opt4_medium" "kerPack_gemm_Opt4_large" "kerPack_gemm_Opt4_extralarge" )

list(APPEND kerPackList "kerPack_gemmPer_Opt0_mini" "kerPack_gemmPer_Opt0_small" "kerPack_gemmPer_Opt0_medium" "kerPack_gemmPer_Opt0_large" "kerPack_gemmPer_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_gemmPer_Opt1_mini" "kerPack_gemmPer_Opt1_small" "kerPack_gemmPer_Opt1_medium" "kerPack_gemmPer_Opt1_large" "kerPack_gemmPer_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_gemmPer_Opt2_mini" "kerPack_gemmPer_Opt2_small" "kerPack_gemmPer_Opt2_medium" "kerPack_gemmPer_Opt2_large" "kerPack_gemmPer_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_gemmPer_Opt3_mini" "kerPack_gemmPer_Opt3_small" "kerPack_gemmPer_Opt3_medium" "kerPack_gemmPer_Opt3_large" "kerPack_gemmPer_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_gemmPer_Opt4_mini" "kerPack_gemmPer_Opt4_small" "kerPack_gemmPer_Opt4_medium" "kerPack_gemmPer_Opt4_large" "kerPack_gemmPer_Opt4_extralarge" )

list(APPEND kerPackList "kerPack_jacobi2d_Opt0_mini" "kerPack_jacobi2d_Opt0_small" "kerPack_jacobi2d_Opt0_medium" "kerPack_jacobi2d_Opt0_large" "kerPack_jacobi2d_Opt0_extralarge" )
list(APPEND kerPackList "kerPack_jacobi2d_Opt1_mini" "kerPack_jacobi2d_Opt1_small" "kerPack_jacobi2d_Opt1_medium" "kerPack_jacobi2d_Opt1_large" "kerPack_jacobi2d_Opt1_extralarge" )
list(APPEND kerPackList "kerPack_jacobi2d_Opt2_mini" "kerPack_jacobi2d_Opt2_small" "kerPack_jacobi2d_Opt2_medium" "kerPack_jacobi2d_Opt2_large" "kerPack_jacobi2d_Opt2_extralarge" )
list(APPEND kerPackList "kerPack_jacobi2d_Opt3_mini" "kerPack_jacobi2d_Opt3_small" "kerPack_jacobi2d_Opt3_medium" "kerPack_jacobi2d_Opt3_large" "kerPack_jacobi2d_Opt3_extralarge" )
list(APPEND kerPackList "kerPack_jacobi2d_Opt4_mini" "kerPack_jacobi2d_Opt4_small" "kerPack_jacobi2d_Opt4_medium" "kerPack_jacobi2d_Opt4_large" "kerPack_jacobi2d_Opt4_extralarge" )




if(${REPLACE_FILES} STREQUAL "true")

    message(STATUS "Replacing kernel files")
    foreach(kerPack IN LISTS kerPackList)

        EXTRACT_KERNEL_FOLDER(${kerPack}, kerPackFolderTemp)

        if(${TARGET} STREQUAL "sw_emu")
        string(CONCAT kerPackTemp ${kerPack} "_sw_emu.xclbin")
        set(fileURLTemp "${CMAKE_CURRENT_SOURCE_DIR}/../build/kernelBuild/${kerPackFolderTemp}/sw_emu/${kerPackTemp}")
        
        elseif (${TARGET} STREQUAL "hw_emu")
        string(CONCAT kerPackTemp ${kerPack} "_hw_emu.xclbin")
        set(fileURLTemp "${CMAKE_CURRENT_SOURCE_DIR}/../build/kernelBuild/${kerPackFolderTemp}/hw_emu/${kerPackTemp}")
        
        elseif (${TARGET} STREQUAL "hw")
        string(CONCAT kerPackTemp ${kerPack} "_hw.xclbin")
        set(fileURLTemp "${CMAKE_CURRENT_SOURCE_DIR}/../build/kernelBuild/${kerPackFolderTemp}/hw/${kerPackTemp}")
        
        else()
        message(FATAL_ERROR "ERROR: TARGET not define.")
        break()
        endif()

        if(EXISTS ${fileURLTemp})
        configure_file(${fileURLTemp} ${CMAKE_CURRENT_BINARY_DIR}/${kerPackTemp} COPYONLY)
        else()
        message(STATUS "Kernels aren't compiled. Compile the kernels and try again ${kerPackTemp}")
        endif()

    endforeach()

else()
    message(STATUS "Selected not replace kernel files")
endif()

#********************************
# COPIYING KERNEL FILES - END *
#********************************




#********************************
# COPIYING PYTHON FILES - START *
#********************************
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_global_performance.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_global_performance.py ${CMAKE_CURRENT_BINARY_DIR}/generateGaphics_global_performance.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateGaphics_global_performance.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_global_power.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_global_power.py ${CMAKE_CURRENT_BINARY_DIR}/generateGaphics_global_power.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateGaphics_global_power.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_performance.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_performance.py ${CMAKE_CURRENT_BINARY_DIR}/generateGaphics_performance.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateGaphics_performance.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_power.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateGaphics_power.py ${CMAKE_CURRENT_BINARY_DIR}/generateGaphics_power.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateGaphics_performance.py file haven't been founded")
endif()



if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_performance.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_performance.py ${CMAKE_CURRENT_BINARY_DIR}/generateTable_performance.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateTable_performance.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_global_power.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_global_power.py ${CMAKE_CURRENT_BINARY_DIR}/generateTable_global_power.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateTable_global_power.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_power.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_power.py ${CMAKE_CURRENT_BINARY_DIR}/generateTable_power.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateTable_power.py file haven't been founded")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_global_performance.py")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../python/generateTable_global_performance.py ${CMAKE_CURRENT_BINARY_DIR}/generateTable_global_performance.py COPYONLY)
else()
  message(FATAL_ERROR "Python generateTable_global_performance.py file haven't been founded")
endif()
#********************************
# COPIYING PYTHON FILES - END *
#********************************




#******************************
# COMPILING HOST APPLICATION *
#******************************
add_library(example_utils STATIC
  ../src/utilities/dateAndTime/dateAndTime.cpp
  ../src/utilities/event_timer/event_timer.cpp
  ../src/utilities/xilinx_ocl_helper/xilinx_ocl_helper.cpp
  ../src/utilities/helper/helper_getNameOfType.cpp
)

target_include_directories(example_utils PUBLIC
  ${XRT_INCLUDE_DIRS}
  ${OpenCL_INCLUDE_DIRS}
)

add_executable(benchmarkExec
  ../src/main.cpp
  
  ../src/host/doitgenHost/doitgenHost.cpp
  ../src/host/doitgenHost/doitgenHost_Opt0/doitgenHost_Opt0.cpp
  ../src/host/doitgenHost/doitgenHost_Opt1/doitgenHost_Opt1.cpp
  ../src/host/doitgenHost/doitgenHost_Opt2/doitgenHost_Opt2.cpp
  ../src/host/doitgenHost/doitgenHost_Opt3/doitgenHost_Opt3.cpp
  ../src/host/doitgenHost/doitgenHost_Opt4/doitgenHost_Opt4.cpp
  ../src/kernel/doitgenKernel/doitgenKernel.cpp
  
  ../src/host/choleskyHost/choleskyHost.cpp
  ../src/host/choleskyHost/choleskyHost_Opt0/choleskyHost_Opt0.cpp
  ../src/host/choleskyHost/choleskyHost_Opt1/choleskyHost_Opt1.cpp
  ../src/host/choleskyHost/choleskyHost_Opt2/choleskyHost_Opt2.cpp
  ../src/host/choleskyHost/choleskyHost_Opt3/choleskyHost_Opt3.cpp
  ../src/host/choleskyHost/choleskyHost_Opt4/choleskyHost_Opt4.cpp
  ../src/kernel/choleskyKernel/choleskyKernel.cpp
  
  ../src/host/jacobi2dHost/jacobi2dHost.cpp
  ../src/host/jacobi2dHost/jacobi2dHost_Opt0/jacobi2dHost_Opt0.cpp
  ../src/host/jacobi2dHost/jacobi2dHost_Opt1/jacobi2dHost_Opt1.cpp
  ../src/host/jacobi2dHost/jacobi2dHost_Opt2/jacobi2dHost_Opt2.cpp
  ../src/host/jacobi2dHost/jacobi2dHost_Opt3/jacobi2dHost_Opt3.cpp
  ../src/host/jacobi2dHost/jacobi2dHost_Opt4/jacobi2dHost_Opt4.cpp
  ../src/kernel/jacobi_2dKernel/jacobi_2dKernel.cpp
  
  ../src/host/gemmHost/gemmHost.cpp
  ../src/host/gemmHost/gemmHost_Opt0/gemmHost_Opt0.cpp
  ../src/host/gemmHost/gemmHost_Opt1/gemmHost_Opt1.cpp
  ../src/host/gemmHost/gemmHost_Opt2/gemmHost_Opt2.cpp
  ../src/host/gemmHost/gemmHost_Opt3/gemmHost_Opt3.cpp
  ../src/host/gemmHost/gemmHost_Opt4/gemmHost_Opt4.cpp
  ../src/kernel/gemmKernel/gemmKernel.cpp

  ../src/host/gemmPerHost/gemmPerHost.cpp
  ../src/host/gemmPerHost/gemmPerHost_Opt0/gemmPerHost_Opt0.cpp
  ../src/host/gemmPerHost/gemmPerHost_Opt1/gemmPerHost_Opt1.cpp
  ../src/host/gemmPerHost/gemmPerHost_Opt2/gemmPerHost_Opt2.cpp
  ../src/host/gemmPerHost/gemmPerHost_Opt3/gemmPerHost_Opt3.cpp
  ../src/host/gemmPerHost/gemmPerHost_Opt4/gemmPerHost_Opt4.cpp
  ../src/kernel/gemmPerKernel/gemmPerKernel.cpp
  
  ../src/host/vectorAddHost/vectorAddHost.cpp
  ../src/host/vectorAddHost/vectorAddHost_Opt0/vectorAddHost_Opt0.cpp
  ../src/host/vectorAddHost/vectorAddHost_Opt1/vectorAddHost_Opt1.cpp
  ../src/host/vectorAddHost/vectorAddHost_Opt2/vectorAddHost_Opt2.cpp
  ../src/host/vectorAddHost/vectorAddHost_Opt3/vectorAddHost_Opt3.cpp
  ../src/host/vectorAddHost/vectorAddHost_Opt4/vectorAddHost_Opt4.cpp
  ../src/kernel/vectorAddKernel/vectorAddKernel.cpp
  
  ../src/host/studyCase1Host/studyCase1Host.cpp
  ../src/host/studyCase1Host/studyCase1Host_a/studyCase1Host_a.cpp
  ../src/host/studyCase1Host/studyCase1Host_b/studyCase1Host_b.cpp
  ../src/host/studyCase1Host/studyCase1Host_c/studyCase1Host_c.cpp
  ../src/kernel/studyCase1Kernel/studyCase1Kernel.cpp
  
  ../src/host/studyCase2Host/studyCase2Host.cpp
  ../src/host/studyCase2Host/studyCase2Host_a/studyCase2Host_a.cpp
  ../src/host/studyCase2Host/studyCase2Host_b/studyCase2Host_b.cpp
  ../src/host/studyCase2Host/studyCase2Host_c/studyCase2Host_c.cpp
  ../src/host/studyCase2Host/studyCase2Host_d/studyCase2Host_d.cpp
  ../src/kernel/studyCase2Kernel/studyCase2Kernel.cpp
  
  ../src/host/studyCase3Host/studyCase3Host.cpp
  ../src/host/studyCase3Host/studyCase3Host_a/studyCase3Host_a.cpp
  ../src/host/studyCase3Host/studyCase3Host_b/studyCase3Host_b.cpp
  ../src/host/studyCase3Host/studyCase3Host_c/studyCase3Host_c.cpp
  ../src/host/studyCase3Host/studyCase3Host_d/studyCase3Host_d.cpp
  ../src/kernel/studyCase3Kernel/studyCase3Kernel.cpp

  ../src/service/fileWriter_service/fileWriter_service.cpp
  ../src/service/json_service/json_service.cpp
  ../src/service/json_service/jsonConfiguration/jsonConfiguration.cpp
  ../src/service/json_service/jsonConfiguration/execution/execution.cpp
  ../src/service/json_service/jsonConfiguration/test/test.cpp
  
  ../src/service/externProgramsConnection_service/externProgramsConnection_service.cpp
  )

target_include_directories(benchmarkExec PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${XRT_INCLUDE_DIRS}
  ${OpenCL_INCLUDE_DIRS}
  ${jsoncpp_INCLUDE_DIRS} 
  /opt/xilinx/xrt/include
  /opt/xilinx/Vitis/2023.2/include
  /opt/xilinx/Vitis_HLS/2023.2/include
  )

target_link_libraries(benchmarkExec PRIVATE
  ${XRT_LIBS}
  ${OpenCL_LIBRARIES}
  ${CMAKE_DL_LIBS}
  jsoncpp_lib
  pthread
  uuid
  example_utils
  OpenMP::OpenMP_CXX
  )

