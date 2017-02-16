# Multicast
Utility for multicast test

# MakeFile for Android
## multicast_server
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        multicast_server.cpp
        
LOCAL_MODULE:= multicast_server

LOCAL_SHARED_LIBRARIES:= \
        libcutils

include $(BUILD_EXECUTABLE)

---
## multicast_client
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        multicast_client.cpp

LOCAL_SHARED_LIBRARIES:= \
        libcutils

LOCAL_MODULE:= multicast_client

include $(BUILD_EXECUTABLE)
