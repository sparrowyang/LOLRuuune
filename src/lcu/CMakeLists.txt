
add_library(lcu STATIC  lcu.cpp lcu.h httplib.h rune_page.cpp rune_page.h json.h)
target_link_libraries(lcu logger)
target_link_libraries(lcu libssl)
target_link_libraries(lcu libcrypto)
