#include <cstdio>
#include <cwchar>

extern "C" int CountWChars_(const wchar_t *s, wchar_t c);
extern "C" int CountChars_(const char *s, char c);

void CountChars1(void);
void CountChars2(void);

int main(void){
//    CountChars1();
//    printf("\n");
    CountChars2();
    printf("\n");


    return 0;
}

void CountChars1(void){
    char c;
    const char *s;

    s = "Four score and seven seconds ago, ...";
    printf("\nTest string: %s\n", s);
    c = L's';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'F';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'o';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'z';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));

    s = "Red Green Blue Cyan Magenta Yellow";
    printf("\nTest string: %s\n", s);
    c = L'e';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'w';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'Q';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
    c = L'l';
    printf("  SearchChar: %c Count: %d\n", c, CountChars_(s, c));
}

void CountChars2(void){
        wchar_t c;
        const wchar_t *s;

        // 使用wchar_t存在问题，其使用4字节表示
        s = L"Four score and seven seconds ago, ...";
        wprintf(L"\nTest string: %s\n", s);
        c = L's';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'F';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'o';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'z';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));

        s = L"Red Green Blue Cyan Magenta Yellow";
        wprintf(L"\nTest string: %s\n", s);
        c = L'e';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'w';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'Q';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
        c = L'l';
        wprintf(L"  SearchChar: %c Count: %d\n", c, CountWChars_(s, c));
}
