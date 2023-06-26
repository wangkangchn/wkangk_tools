set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
find_package(GTest REQUIRED)
find_package(gflags  REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(Thirdparty_Libs     pthread
                        GTest::GTest GTest::Main
                        gflags gmock
                    )
                    
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(EXTRA_SRCS "${PROJECT_SOURCE_DIR}/logger/logger.cpp")

macro(_unittest unittest_name)
    target_link_libraries( ${unittest_name}  ${Thirdparty_DIRECTORIES} ${Thirdparty_Libs} )
    add_test(  NAME  ${unittest_name}  COMMAND    ${CMAKE_BINARY_DIR}/test/${unittest_name}  )
endmacro(_unittest)

macro(add_unittest unittest_name)
    add_executable( ${unittest_name} "${unittest_name}.cpp"  ${EXTRA_SRCS})
    _unittest(${unittest_name})
endmacro(add_unittest)

macro(add_unittest_multi unittest_name src)
    add_executable( ${unittest_name} "${unittest_name}.cpp" ${src}   ${EXTRA_SRCS})
    _unittest(${unittest_name})
endmacro(add_unittest_multi)


add_unittest(unittest_logger)
add_unittest(unittest_threadobject)
add_unittest(unittest_threadpool)
