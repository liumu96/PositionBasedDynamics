#pragma once

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define WARNING(desc) message(__FILE__ "(" STRINGIZE(__LINE__) ") : Warning: " #desc)

#define GIT_SHA1 "4e72f63dee418a450fc2328cce8ff5b93006d301"
#define GIT_REFSPEC "refs/heads/main"
#define GIT_LOCAL_STATUS "DIRTY"

#define PBD_VERSION "2.2.0"

#ifdef DL_OUTPUT
@COMPILER_MESSAGE @
#endif
