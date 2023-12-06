#pragma once

#include <string>

class AbstractCalculator {
public:
    virtual double calculate(const std::string& input) = 0;
    virtual ~AbstractCalculator() {}

    static AbstractCalculator* createCalculator(); // Фабричный метод
};