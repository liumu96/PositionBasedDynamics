#pragma once

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define WARNING(desc) message(__FILE__ "(" STRINGIZE(__LINE__) ") : Warning: " #desc)

#define GIT_SHA1 "4fb0de0f09251a8ed52ed48307a9023a2c5c4330"
#define GIT_REFSPEC "refs/heads/main"
#define GIT_LOCAL_STATUS "DIRTY"

#define PBD_VERSION "2.2.0"

#ifdef DL_OUTPUT
@COMPILER_MESSAGE @
#endif
