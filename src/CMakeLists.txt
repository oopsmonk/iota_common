add_library(iota_common
	"crypto/kerl/bigint.c"
	"crypto/kerl/converter.c"
	"crypto/kerl/kerl.c"
	"crypto/signing.c"
	"model/address.c"
	"model/transaction.c"
	"ternary/ternary.c"
	"utils/memset_safe.c"
)

target_include_directories(iota_common PUBLIC 
	${PROJECT_SOURCE_DIR}/src 
	${IOTA_COMMON_EXTERNAL_HEADERS}
)

add_dependencies(iota_common ext_keccak)
target_link_libraries(iota_common PUBLIC keccak)
if(HAS_ASAN_ENABLED)
  target_link_libraries(iota_common PUBLIC asan)
endif()

# install
install(TARGETS iota_common DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" FILES_MATCHING PATTERN "*.h")