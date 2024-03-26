#include <iostream>
#include <cstdlib>
#include <ctime>
#include "image_menu.h"

int main() {
    std::srand(std::time(0)); //seed rand once at start
    int result;
    result = imageMenu(std::cin, std::cout);
    return result;
}
