#include "Diffie-Hellman.h"
#include <iostream>

int main()
{
    uint64_t p, g;

    while(true)
    {

        std::cout << "p : ";
        std::cin >> p;
        std::cout << "g : ";
        std::cin >> g;

        if(p == 0)
        {
            break;
        }

        uint64_t data = GenerateExchangeData(p, g);
        std::cout << "data : " << data << std::endl;
        std::cout << "Other' Data : ";
        std::cin >> data;
        uint64_t key = GenerateExchangeKey(data);
        std::cout << "ExchangeKey : " << key << std::endl;
    }
    return 0;
}