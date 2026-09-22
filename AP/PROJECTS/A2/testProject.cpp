#include <iostream>
#include <string>
#include <vector>
#include <limits>

bool findMirror(const std::string &givenString, int leftCheckIndex, int rightCheckIndex);
void printResult(const std::vector<std::string> &results, int startIndex = 0);
std::vector<std::string> processTests();
int findLeftIndex(const std::string &givenString, int &leftCheckIndex);
int findRightIndex(const std::string &givenString, int &rightCheckIndex);

#define DIF_ASCII 32
#define MAX_ASCII_UP 122
#define MIN_ASCII_UP 97
#define MAX_ASCII_DOWN 90
#define MIN_ASCII_DOWN 65

int main()
{
    std::vector<std::string> results = processTests();

    printResult(results);

    return 0;
}

std::vector<std::string> processTests()
{

    int testCaseCount;

    if (!(std::cin >> testCaseCount))
    {
        std::cerr << "Envalid input : the number of tests should be an int."
                  << std::endl;

        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return {};
    }

    std::vector<std::string> results;
    results.reserve(testCaseCount);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int test = 0; test < testCaseCount; test++)
    {
        std::string givenSentence;

        std::getline(std::cin, givenSentence);

        if (givenSentence.empty())
        {
            results.emplace_back("yes");
            continue;
        }

        size_t leftCheckIndex = 0;
        size_t rightCheckIndex = givenSentence.length() - 1;

        bool isMirror = findMirror(givenSentence, leftCheckIndex, rightCheckIndex);

        if (isMirror)
        {
            results.emplace_back("yes");
        }
        else
        {
            results.emplace_back("no");
        }
    }

    return results;
}

bool findMirror(const std::string &givenString, int leftCheckIndex, int rightCheckIndex)
{

    findLeftIndex(givenString, leftCheckIndex);
    findRightIndex(givenString, rightCheckIndex);

    if (rightCheckIndex <= leftCheckIndex)
    {
        return true;
    }
    else if (givenString[rightCheckIndex] - givenString[leftCheckIndex] != DIF_ASCII
            && givenString[leftCheckIndex] - givenString[rightCheckIndex] != DIF_ASCII
            && givenString[rightCheckIndex] != givenString[leftCheckIndex])
    {
        return false;
    }
    else
    {
        rightCheckIndex--;
        leftCheckIndex++;

        return findMirror(givenString, leftCheckIndex, rightCheckIndex);
    }
}

void printResult(const std::vector<std::string> &results, int startIndex)
{
    if(startIndex == results.size()){
        return;
    }

    std::cout << results[startIndex]
        << std::endl;

    startIndex += 1;
    
    printResult(results, startIndex);
}

int findRightIndex(const std::string &givenString, int &rightCheckIndex)
{
    if (((givenString[rightCheckIndex] >= MIN_ASCII_DOWN 
        && givenString[rightCheckIndex] <= MAX_ASCII_DOWN)
        || (givenString[rightCheckIndex] >= MIN_ASCII_UP
        && givenString[rightCheckIndex] <= MAX_ASCII_UP))
        || rightCheckIndex <= 0)
    {
        return rightCheckIndex;
    }

    rightCheckIndex--;
    findRightIndex(givenString, rightCheckIndex);

    return rightCheckIndex;
}

int findLeftIndex(const std::string &givenString, int &leftCheckIndex)
{
    if (((givenString[leftCheckIndex] >= MIN_ASCII_DOWN 
        && givenString[leftCheckIndex] <= MAX_ASCII_DOWN)
        || (givenString[leftCheckIndex] >= MIN_ASCII_UP
        && givenString[leftCheckIndex] <= MAX_ASCII_UP))
        || leftCheckIndex >= givenString.length())
    {
        return leftCheckIndex;
    }

    leftCheckIndex++;
    findLeftIndex(givenString, leftCheckIndex);

    return leftCheckIndex;
}