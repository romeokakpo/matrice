#include "matrice.h"
#include <cmath>

int main()
{
    Matrice a(3,3,{5,1,-2,3,2,1,2,3,-2}),
            b(3,3,{2,3,1,3,2,3,4,2,4}),c(3);
    c.diag(5);
    std::cout<<c<<'\n';
    return 0;
}
