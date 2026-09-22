#include <iostream>
#include <string>
#include <limits>

const int MIN_DUPLICATION_COUNT = 1;
const int START_INDEX = 0;
const int DIF_ASCII = 32;
const int MAX_ASCII_UP = 122;
const int MIN_ASCII_UP = 97;
const int MAX_ASCII_DOWN = 90;
const int MIN_ASCII_DOWN = 65;
const int MIN_ASCII_NUMBER = 48;
const int MAX_ASCII_NUMBER = 57; 


std::string repeatString(const std::string& repeatedWord, const int repeatCount , int opearationCount = 0){

    if(opearationCount >= repeatCount){
        return "";
    }

    opearationCount += 1;

    return  repeatedWord + repeatString(repeatedWord, repeatCount, opearationCount);
}

std::string findRepeatNumber(const std::string& givenString, size_t& index){
    std::string strRepeat = "";

    if(givenString[index] >= MIN_ASCII_NUMBER 
        && givenString[index] <= MAX_ASCII_NUMBER)
        {
            strRepeat += givenString[index];
        }
    else
    {
        return strRepeat;
    }
    
    index += 1;

    return strRepeat + findRepeatNumber(givenString, index);
}

std::string findSecret(std::string &givenString, size_t &startIndex)
{

    std::string secretString = "";

    int repeatCount = MIN_DUPLICATION_COUNT;
    for (size_t index = startIndex; index < givenString.length(); index++)
    {

        if (givenString[index] >= MIN_ASCII_NUMBER
            && givenString[index] <= MAX_ASCII_NUMBER)
        {
            std::string strDuplicationNumber = findRepeatNumber(givenString, index);

            index -= 1;

            if (givenString[index + 1] != '[')
            {
                secretString += strDuplicationNumber;
            }
            else
            {
                repeatCount = std::stoi(strDuplicationNumber);
                strDuplicationNumber = "";
            }
        }
        else if ((givenString[index] >= MIN_ASCII_DOWN
                && givenString[index] <= MAX_ASCII_DOWN)
                || (givenString[index] >= MIN_ASCII_UP
                && givenString[index] <= MAX_ASCII_UP))
        {
            secretString += givenString[index];
        }
        else if (givenString[index] == ']')
        {
            startIndex = index;
            return secretString;
        }
        else if (givenString[index] == '[')
        {
            index += 1;

            std::string base = findSecret(givenString, index);
            std::string repeatBase = repeatString(base, repeatCount);
            secretString += repeatBase;
            repeatCount = 1;
        }
    }

    return secretString;
}

int main()
{
    std::string givenString;
    while (std::getline(std::cin, givenString))
    {
        size_t startIndex = START_INDEX;
        std::string secretString = findSecret(givenString, startIndex);
    
        std::cout << secretString << std::endl;
    }
    return 0; 
}