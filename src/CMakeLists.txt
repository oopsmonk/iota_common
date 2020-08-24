
add_library(iota_common
	"models/address.c"
	"models/balance.c"
	# "models/transaction.c"
	"models/inputs/utxo_input.c"
	"models/outputs/sig_unlocked_single_deposit.c"
)

target_include_directories(iota_common PUBLIC 
	${PROJECT_SOURCE_DIR}/src 
	${IOTA_COMMON_EXTERNAL_HEADERS}
)

add_dependencies(iota_common sodium ext_base58 ext_uthash)

set(IOTA_COMMON_EXT_LIBS 
	base58
	libsodium.a
)

target_link_libraries(iota_common PUBLIC ${IOTA_COMMON_EXT_LIBS})

if(HAS_ASAN_ENABLED)
  target_link_libraries(iota_common PUBLIC asan)
endif()

# install
install(TARGETS iota_common DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" FILES_MATCHING PATTERN "*.h")