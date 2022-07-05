#include "Stone.hpp"

int main()
{
    testB({}, 0, { -1, -1 });
    testB({ 1, 3, 5, 7 }, 2, { 0, 1 });
    testB({ 1, 3, 1 }, 2, { 0, 1 });
    testB({ 1, 3, 5, 7 }, 3, { -1, -1 });
    return 0;
}
