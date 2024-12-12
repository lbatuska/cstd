
#if defined __clang__ && !defined __cplusplus
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Wall"
#pragma clang diagnostic warning "-Wextra"
#pragma clang diagnostic warning "-Wincompatible-pointer-types"
#elif defined __GNUC__ && !defined __cplusplus
#pragma GCC diagnostic push
#pragma GCC diagnostic warning "-Wall"
#pragma GCC diagnostic warning "-Wextra"
#pragma GCC diagnostic warning "-Wincompatible-pointer-types"
#endif
