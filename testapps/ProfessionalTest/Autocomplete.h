#include "../Algorithms/trees/ternary_search_tree.h"

#include <thread>
#include <fstream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <algorithm>

std::ifstream f("/usr/share/dict/british-english");
std::string currentWord;
std::mutex m;
std::condition_variable cv;
bool ready = false;
TernaryTree ternaryTree;
bool endOfFile = false;

inline bool isLowerCase(const std::string& word)
{
    for(unsigned int i=0; i< word.size(); ++i)
    {
        if (word[i] < 'a' || word[i] > 'z')
        {
            return false;
        }
    }

    return true;
}

void createDictionary()
{
    while (f)
    {
        std::string word;
        f >> word;
        if (isLowerCase(word))
        {
            //std::cout << "adding " << word << std::endl;
            ternaryTree.insert((char*)word.c_str());
        }
    }
}

int checkIfMatch(const char* typed, const char* suggestion)
{
    double incorrectTolerancePercentage = 0.2;
    double lengthTolerancePercentage = 0.1;
    int suggestionLen = strlen(suggestion);
    int typedLen = strlen(typed);

    if (abs(suggestionLen - typedLen) >= (lengthTolerancePercentage * typedLen + 1))
    {
        return -1;
    }

    // check if by skipping/removing one letter we get a match
    {
        int length = suggestionLen > typedLen ? suggestionLen : typedLen;
        char* word1 = nullptr;
        char* word2 = nullptr;

        if (suggestionLen > typedLen)
        {
            word1 = (char*)suggestion;
            word2 = (char*)typed;
        }
        else
        {
            word1 = (char*)typed;
            word2 = (char*)suggestion;
        }

        bool wordsSimilar = true;

        for (int skip = 0; skip < length; ++skip)
        {
            wordsSimilar = true;

            for (int i = 0, j = 0; i < length; ++i)
            {
                if (i == skip)
                {
                    continue;
                }
                else
                {
                    if (word1[i] != word2[j])
                    {
                        wordsSimilar = false;
                        break;
                    }

                    j++;
                }
            }

            if (wordsSimilar)
            {
                break;
            }
        }

        if (wordsSimilar)
        {
            return 0;
        }
    }

    // we are assuming that the first character needs to be correct
    int numberOfInccorectWordsExpected = incorrectTolerancePercentage * strlen(typed) + 1;
    int numbberOfIncorrectWords = 0;

    for(unsigned int i=0; i< strlen(typed); ++i)
    {
        if (typed[i] != suggestion[i])
        {
            ++numbberOfIncorrectWords;
        }

        if (numbberOfIncorrectWords > numberOfInccorectWordsExpected)
        {
            return -1;
        }
    }

    return 0.6 * abs(suggestionLen - typedLen) + 0.4*numbberOfIncorrectWords;
}

bool checkIfWordExists(char *argv[], int count, const char* suggestion)
{
    for(int i=0; i< count; ++i)
    {
        if (strcmp(argv[i], suggestion) == 0)
        {
            return true;
        }
    }

    return false;
}

void displayThread()
{
    while(1)
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return ready;});

        std::cout << "searching for " << currentWord << std::endl;

        auto node = ternaryTree.find((char*)currentWord.c_str());
        if (!node.lastNode)
        {
            auto copyOrigWord = currentWord;
            auto l = [copyOrigWord](char* suggestion1, char* suggestion2)
            {
               auto match1 = checkIfMatch(copyOrigWord.c_str(), suggestion1);
               auto match2 = checkIfMatch(copyOrigWord.c_str(), suggestion2);

               return match1 < match2;

            };

            const unsigned maxSuggestions = 100;
            char* suggestions[maxSuggestions];
            int count = 0;

            while(!currentWord.empty())
            {
                currentWord.pop_back();
                std::cout << "no words found at all, trying auto correct: " << currentWord << std::endl;

                auto node = ternaryTree.find((char*)currentWord.c_str());
                if (!node.lastNode)
                {
                    continue;
                }

                TernaryTree::Result result;
                ternaryTree.traverse(node.lastNode, &result);

                for(unsigned i=0; i< result.count; ++i)
                {
                    const char* suggestion = (currentWord + std::string(result.result[i]) ).c_str();
                    if (checkIfMatch(copyOrigWord.c_str(), suggestion) != -1 && !checkIfWordExists(suggestions, count, suggestion))
                    {
                        suggestions[count] = strdup(suggestion);
                        if (count + 1 < maxSuggestions)
                        {
                            ++count;
                        }
                        else
                        {
                            std::sort(suggestions,suggestions + count, l);
                        }
                    }
                }
              }

            std::sort(suggestions,suggestions + count, l);
            for(unsigned int i=0; i< count; ++i)
            {
                std::cout << suggestions[i] << std::endl;
            }
        }
        else if (node.lastNode)
        {

        }

        ready = false;

        if (endOfFile)
        {
            return;
        }
    }
}

void readThread()
{
    // send data to the worker thread

    while(1)
    {
        char c = getchar();
        if (c == '\n')
        {
            continue;
        }
        else if (c == EOF)
        {
            endOfFile = true;
            return;
        }

        std::lock_guard < std::mutex > lk(m);
        currentWord.push_back(c);
        ready = true;
        //std::cout << "main() signals data ready for processing\n";

        cv.notify_one();
    }
}

void init()
{
    createDictionary();
    std::thread r(readThread);
    std::thread w(displayThread);

    r.join();
    w.join();
}

