#include "main.h"
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
#  include <windows.h>
typedef HMODULE OvlHandle;
#  define OVL_EXT ".dll"
#  define OVL_PREFIX ""
static OvlHandle OvlOpen(const char* path) { return LoadLibraryA(path); }
static void* OvlSym(OvlHandle h, const char* name) {
    return (void*)GetProcAddress(h, name);
}
static void OvlClose(OvlHandle h) { FreeLibrary(h); }
static const char* OvlError(void) { return "LoadLibrary/GetProcAddress failed"; }

#else
#  include <dlfcn.h>
typedef void* OvlHandle;
#  if defined(__APPLE__)
#    define OVL_EXT ".dylib"
#  else
#    define OVL_EXT ".so"
#  endif
#  define OVL_PREFIX "./"
static OvlHandle OvlOpen(const char* path) {
    return dlopen(path, RTLD_NOW | RTLD_LOCAL);
}
static void* OvlSym(OvlHandle h, const char* name) { return dlsym(h, name); }
static void OvlClose(OvlHandle h) { dlclose(h); }
static const char* OvlError(void) { return dlerror(); }

#endif

bool LoadOverlay(struct Overlay* ovl, const char* ovl_path) {
    memset(ovl, 0, sizeof(struct Overlay));

    char sopath[256];
    snprintf(sopath, sizeof(sopath), "%s%s%s", OVL_PREFIX, ovl_path, OVL_EXT);

    OvlHandle handle = OvlOpen(sopath);
    if (!handle) {
        fprintf(stderr, "failed to load %s: %s\n", sopath, OvlError());
        return false;
    }

    struct Overlay* header = (struct Overlay*)OvlSym(handle, "header");
    if (!header) {
        fprintf(stderr, "no header in %s: %s\n", sopath, OvlError());
        OvlClose(handle);
        return false;
    }

    *ovl = *header;
    return true;
}
