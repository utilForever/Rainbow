//
// Created by hanel on 2017. 10. 11..
//

#ifndef DIFFIE_HELLMAN_DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_DIFFIE_HELLMAN_H

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <random>

class DiffieHellmanUtil
{
public:
    void SetPModule(uint64_t pModule);
    void SetModule(uint64_t module);

    uint64_t DiffieHellmanCalc();

    void Clear();

private:
    uint64_t GenerateRandModule();
    bool IsPrime(uint64_t pModule);

    const uint64_t MAX_SIZE = static_cast<uint64_t>(pow(2, 4));

    uint64_t m_pModule = 0;
    uint64_t m_module = 0;
    uint64_t m_randModule = GenerateRandModule();

} util;

uint64_t GenerateExchangeData(uint64_t pModule, uint64_t gModule)
{
    if(pModule <= gModule)
    {
        throw std::invalid_argument("gModule is not bigger than pModule.");
    }
    util.SetPModule(pModule);
    util.SetModule(gModule);
    uint64_t data = util.DiffieHellmanCalc();

    return data;
}

uint64_t GenerateExchangeKey(uint64_t responseData)
{
    util.SetModule(responseData);
    uint64_t key = util.DiffieHellmanCalc();
    util.Clear();

    return key;
}

void DiffieHellmanUtil::SetPModule(uint64_t pModule)
{
    if(!IsPrime(pModule))
    {
        throw std::invalid_argument("pModule is not prime number.");
    }

    m_pModule = pModule;
}

void DiffieHellmanUtil::SetModule(uint64_t module)
{
    m_module = module;
}

uint64_t DiffieHellmanUtil::DiffieHellmanCalc()
{
    uint64_t data = static_cast<uint64_t >(pow(m_module, m_randModule)) % m_pModule;

    return data;
}

void DiffieHellmanUtil::Clear()
{
    m_pModule = 0;
    m_module = 0;
    m_randModule = 0;
}

uint64_t DiffieHellmanUtil::GenerateRandModule()
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	uint64_t data = mt() % MAX_SIZE + 1;

	return data;
}

bool DiffieHellmanUtil::IsPrime(uint64_t pModule)
{
    if (pModule == 1)
    {
        return false;
    }

    if ((pModule & 1) == 0)
    {
        return pModule == 2;
    }

    for (uint64_t i = 2; i * i < pModule; i+=2)
    {
        if(pModule % i == 0)
        {
            return false;
        }
    }

    return true;
}

#endif //DIFFIE_HELLMAN_DIFFIE_HELLMAN_H
