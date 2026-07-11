#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

#ifdef _WIN32
#  ifndef IS_OVERLAY
#    define MAIN_API __declspec(dllexport)
#  else
#    define MAIN_API __declspec(dllimport)
#  endif
#else
#define MAIN_API
#endif

/*
 * OVL_API marks the public symbol an overlay exposes to main (`header`).
 * On Windows it must be dllexport'd from the overlay DLL so main's GetProcAddress
 * can find it; elsewhere dlsym finds any global symbol without decoration.
 */
#if defined(_WIN32)
#  define OVL_API __declspec(dllexport)
#else
#  define OVL_API
#endif

struct Api {
    void (*Print)(const char* str);
};

struct Overlay {
    void (*Entrypoint)(const char* str);
};

MAIN_API extern struct Api api;

MAIN_API void PrintHeader(void);

bool LoadOverlay(struct Overlay* ovl, const char* ovl_path);

#endif
