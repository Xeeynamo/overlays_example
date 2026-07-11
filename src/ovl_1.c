#include "main.h"

static void Ovl1(const char* str) {
    PrintHeader();
    api.Print("hello from OVL 1");
    api.Print(str);
}

struct Overlay header = { Ovl1 };
