#include <iostream>

bool validation(std::string realNumber)
{
    bool point = false;
    bool digit = false;
    if (realNumber[0] == '.') point = true;
    else if (realNumber[0] >= '0' && realNumber[0] <= '9') digit = true;
    else if (realNumber[0] != '-') return false;
    if (realNumber.length() > 1)
    {
        for (int i = 1; i < realNumber.length(); i++)
        {
            if (realNumber[i] == '.')
            {
                if (point) return false;
                point = true;
                continue;
            }
            else if (realNumber[i] >= '0' && realNumber[i] <= '9')
            {
                digit = true;
                continue;
            }
            return false;
        }
    }
    if (digit) return true;
    return false;
}

std::string part(std::string realNumber, int p)
{
    if (realNumber.find('.') == std::string::npos)
    {
        if (p == 1) return realNumber;
        if (p == 2) return "0";
    }
    std::string xPart;
    if (p == 1) xPart = realNumber.substr(0,realNumber.find('.'));
    if (p == 2) xPart = realNumber.substr(realNumber.find('.') + 1);
    if (xPart == "-" || xPart.length() == 0) xPart += '0';
    return xPart;
}

std::string normalFractional(std::string fractional)
{
    for (int i = fractional.length() - 1; i > 0; i--)
    {
        if (fractional[i] == '0') fractional = fractional.substr(0,i);
        else break;
    }
    return fractional;
}

int comparison(std::string realNumberOne, std::string realNumberTwo)
{
    // 1 - Less
    // 2 - More
    // 3 - Equal
    std::string integerOne = part(realNumberOne,1);
    std::string integerTwo = part(realNumberTwo,1);
    // отброс минуса и флаг на будущее
    bool negativeOne = false;
    bool negativeTwo = false;
    if (integerOne[0] == '-')
    {
        integerOne = integerOne.substr(1);
        negativeOne = true;
    }
    if (integerTwo[0] == '-')
    {
        integerTwo = integerTwo.substr(1);
        negativeTwo = true;
    }
    //отброс лишних нулей
    int stop = integerOne.length() - 1;
    for (int i = 0; i < stop; i++)
    {
        if (integerOne[0] == '0') integerOne = integerOne.substr(1);
        else break;
    }
    stop = integerTwo.length() - 1;
    for (int i = 0; i < stop; i++)
    {
        if (integerTwo[0] == '0') integerTwo = integerTwo.substr(1);
        else break;
    }
    //сравнение целой части
    if (integerOne.length() > integerTwo.length())
    {
        if (!negativeOne && !negativeTwo) return 2;
        else return 1;
    }
    if (integerOne.length() < integerTwo.length())
    {
        if (!negativeOne && !negativeTwo) return 1;
        else return 2;
    }
    for (int i = 0; i < integerOne.length(); i++)
    {
        if (integerOne[i] == integerTwo[i]) continue;
        if (integerOne[i] > integerTwo[i])
        {
            if (!negativeOne && !negativeTwo) return 2;
            else return 1;
        }
        else
        {
            if (!negativeOne && !negativeTwo) return 1;
            else return 2;
        }
    }
    std::string fractionalOne = normalFractional(part(realNumberOne,2));
    std::string fractionalTwo = normalFractional(part(realNumberTwo,2));
    // выравнивание длины дробных частей
    if (fractionalOne.length() > fractionalTwo.length())
    {
        for (int i = fractionalTwo.length(); i != fractionalOne.length(); i++)
        {
            fractionalTwo += '0';
        }
    }
    else if (fractionalOne.length() < fractionalTwo.length())
    {
        for (int i = fractionalOne.length(); i != fractionalTwo.length(); i++)
        {
            fractionalOne += '0';
        }
    }
    // сравнивание дробной части
    for (int i = 0; i < fractionalOne.length(); i++)
    {
        if (fractionalOne[i] == fractionalTwo[i]) continue;
        if ((fractionalOne[i] > fractionalTwo[i]))
        {
            if (!negativeOne && !negativeTwo) return 2;
            else return 1;
        }
        else
        {
            if (!negativeOne && !negativeTwo) return 1;
            else return 2;
        }
    }
    //если численно равны, проверяем с учётом знака
    if (integerOne == "0") return 3;
    if (!negativeOne && negativeTwo) return 2;
    if (negativeOne && !negativeTwo) return 1;
    return 3;
}

int main() {
    std::string realNumberOne, realNumberTwo;
    std::cout << "First real number:\n";
    std::cin >> realNumberOne;
    if (!validation(realNumberOne)) std::cout << "Input Error\n";
    else
    {
        std::cout << "Second real number:\n";
        std::cin >> realNumberTwo;
        if (!validation(realNumberTwo)) std::cout << "Input Error\n";
        else
        {
            if (comparison(realNumberOne, realNumberTwo) == 1) std::cout << "Less\n";
            else if (comparison(realNumberOne, realNumberTwo) == 2) std::cout << "More\n";
            else std::cout << "Equal\n";
        }
    }
}