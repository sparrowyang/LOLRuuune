add_library(mainwnd STATIC mainwnd.cpp mainwnd.h)
# target_link_libraries(lcu logger)
target_link_libraries(mainwnd PRIVATE Qt5::Widgets)
target_link_libraries(mainwnd PRIVATE lcu)