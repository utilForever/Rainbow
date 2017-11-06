//
// Created by hanel on 2017. 10. 11..
//

#ifndef DIFFIE_HELLMAN_DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_DIFFIE_HELLMAN_H

#pragma once
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <random>

class DiffieHellmanUtil
{
public:
    void setPModule(uint64_t _pModule)
    {
        if(!Prime(_pModule))
        {
            throw std::invalid_argument("pModule is not prime number.");
        }
        pModule = _pModule;
    }

    void setModule(uint64_t _module)
    {
        module = _module;
    }

    uint64_t DiffieHellmanCalc()
    {
        uint64_t data = (uint64_t) pow(module, randModule) % pModule;

        return data;
    }

    uint64_t GenerateRandModule()
    {
        std::random_device rd;
        std::mt19937_64 mt(rd());
        uint64_t data = mt() % MAX_SIZE + 1;

        return data;
    }

    void remove()
    {
        pModule = 0;
        module = 0;
        randModule = 0;
    }

    uint64_t getPModule()
    {
        return pModule;
    }

private:
    bool Prime(uint64_t _pModule)
    {
        if (_pModule == 1)
        {
            return false;
        }

        if ((_pModule & 1) == 0)
        {
            return _pModule == 2;
        }

        for (uint64_t i = 2; i * i < _pModule; i+=2)
        {
            if(_pModule % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    const uint64_t MAX_SIZE =  (uint64_t) pow(2, 4);

    uint64_t pModule;
    uint64_t module;
    uint64_t randModule = GenerateRandModule();
} util;

uint64_t GenerateExchangeData(uint64_t pModule, uint64_t gModule)
{
    if(pModule <= gModule)
    {
        throw std::invalid_argument("module is not bigger than pModule.");
    }
    util.setPModule(pModule);
    util.setModule(gModule);
    uint64_t data = util.DiffieHellmanCalc();

    return data;
}

uint64_t GenerateExchangeKey(uint64_t responseData)
{
    util.setModule(responseData);
    uint64_t key = util.DiffieHellmanCalc();
    util.remove();

    return key;
}

#endif //DIFFIE_HELLMAN_DIFFIE_HELLMAN_H
