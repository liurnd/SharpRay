AUX_SOURCE_DIRECTORY(. src_manger)

ADD_LIBRARY(libsharpray_mgr STATIC ${src_manger})
TARGET_LINK_LIBRARIES(libsharpray_mgr libsharpray)
TARGET_LINK_LIBRARIES(libsharpray_mgr getopt)