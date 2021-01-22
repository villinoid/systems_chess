#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "");
    wchar_t king = 0x2654;
    wprintf(L"%lc\n", king);
}