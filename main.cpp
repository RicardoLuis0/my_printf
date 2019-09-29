#include "printf.h"

int main() {
    My::printf("This is a test %{}\n%{}\n","this is a test2",My::sprintf("%010{},%c{}",2241421,'d'));
    return 0;
}
