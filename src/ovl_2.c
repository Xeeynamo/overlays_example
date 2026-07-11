#define IS_OVERLAY
#include "main.h"

static void Ovl2(const char* str) {
    PrintHeader();
    api.Print("hello from OVL 2");
    api.Print(str);
}

OVL_API struct Overlay header = { Ovl2 };
