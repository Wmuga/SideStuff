#if defined(BUILD_DLL)
#  define DLL_EXP __declspec(dllexport)
#else
#  define DLL_EXP __declspec(dllimport)
#endif


#if defined(__cplusplus)
    extern "C" {
#endif


int DLL_EXP add(int a,int b);


#if defined(__cplusplus)
}
#endif