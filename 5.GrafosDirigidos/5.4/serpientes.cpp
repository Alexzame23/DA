#include <iostream>
#include <limits>

int main() {
    std::cout << "El valor máximo de un int es: " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "El valor mínimo de un int es: " << std::numeric_limits<int>::min() << std::endl;
    return 0;
}
