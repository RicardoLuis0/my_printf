#include "printf.h"

int main() {
    My::printf("This is a test %{}\n%{}\n","this is a test2",My::sprintf("%2{}",2241421));
    return 0;
}
