#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

// counts the occurence of specific items
void searchItem()
{
    std::string word, targetWord;
    int frequency = 0;
    std::cout << "Enter the iteam you're looking for.";
    std::cin >> targetWord;

    std::ifstream file("later.txt");
    if (!file)
    {
        std::cerr << "error opening file" << std::endl;
        return;
    }

    // this is crucial for the search feature, any issues with capitilization
    std::transform(targetWord.begin(), targetWord.end(), targetWord.begin(), ::tolower);

    // this is to search the file specifically, it has already been converted for case sensitvitiy
    while (file >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // searches file for word frequency and iterates to increase count
        if (word == targetWord)
        {
            frequency++
        }
    }

    file.close();

    std::cout << "We have " << frequency << targetWord << "s currently" << std::endl;
}

void printItemCounts()
{
    std::ifstream file("later.txt");
    if (!file)
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // this syntax is a bit strange, but it's specific to our map library
    std::map<std::string, int> itemCounts;
    std::string word;

    while (file >> word)
    {

        // this logic we recycle a lot throughout the code, the basic idea of reading our file is the same, just the output is different for each menu
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        itemCounts[word]++;
    }
    file.close();

    // print each item and it's quantity
    for (const auto &pair : itemCounts)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void printHistogram()
{
    std::ifstream file("later.txt");
    if (!file)
    {
        std::cerr << "error opening file" << std::endl;
        return;
    }

    // same as before, we're using the map specific syntax for our library
    std::map<std::string, int> itemCounts;
    std::string word;

    while (file >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        itemCounts[word]++;
    }
    file.close();

    // this time we're specifically printing a histogram with *
    for (const auto &pair : itemCounts)
    {
        std::cout << pair.first << ": " << std::string(pair.second, '*') << std::endl;
    }
}

int main()
{
    int choice;

    // menu choices
    do
    {
        std::cout << "Select your menu option.\n";
        std::cout << "1) Search for an item\n";
        std::cout << "2) Print all item counts\n";
        std::cout << "3) Print all items as histogram\n";
        std::cout << "4) Quit\n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            searchItem();
            break;

        case 2:
            printItemCounts();
            break;

        case 3:
            printHistogram();
            break;

        case 4:
            std::cout << "thanks for shopping!" << std::endl;
            break;

        default:
            std::cout << "Invalid choice, please use a number.\n";
            break;
        }
    } while (choice != 4);
    return 0;
}