#pragma once

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define WARNING(desc) message(__FILE__ "(" STRINGIZE(__LINE__) ") : Warning: " #desc)

#define GIT_SHA1 "cddd3ecaf74f7ff5e03718495b5cb8d1048f1bb8"
#define GIT_REFSPEC "refs/heads/main"
#define GIT_LOCAL_STATUS "CLEAN"

#define PBD_VERSION "2.2.0"

#ifdef DL_OUTPUT
@COMPILER_MESSAGE @
#endif
