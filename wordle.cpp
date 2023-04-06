#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle(const std::set<std::string>& wordBank, size_t marker, std::string floatPtr, std::string isItCorrect, std::set<std::string>& answer); 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> end; 
    wordle(dict,0, floating, in, end); 
    return end; 
}

// Define any helper functions here
void wordle(const std::set<std::string>& wordBank, size_t marker, std::string floatPtr, std::string isItCorrect, std::set<std::string>& answer)
{
  int dashMark = 0; 
  string correctLetters = floatPtr; 

  if(floatPtr.empty() && marker == isItCorrect.size())
  {
    if(wordBank.find(isItCorrect) != wordBank.end())
    {
      answer.insert(isItCorrect); 
    }
    return;
  }

  if(isItCorrect[marker] != '-')
  {
    wordle(wordBank, marker+1, floatPtr, isItCorrect, answer); 
    return; 
  }

  for(size_t i = 0; i < isItCorrect.size(); i++)
  {
    if(isItCorrect[i] == '-')
    {
      dashMark++; 
    }
  }

  if(dashMark == (int)correctLetters.size())
  {
    for(size_t i = 0; i < correctLetters.size(); i++)
    {
      isItCorrect[marker] = correctLetters[i]; 
      string temp = correctLetters; 
      temp.erase(i,1); 
      wordle(wordBank, marker+1, temp, isItCorrect, answer); 
    }
  }
  else if (dashMark > (int)correctLetters.size())
  {
    for(char c = 'a'; c <= 'z'; c++)
    {
      if(correctLetters.find(c) != string::npos)
      {
        isItCorrect[marker] = c; 
        string temp = correctLetters; 
        temp.erase(correctLetters.find(c), 1); 
        wordle(wordBank, marker+1 , temp, isItCorrect, answer); 
      }
      else
      {
        isItCorrect[marker] = c; 
        wordle(wordBank, marker+1, correctLetters, isItCorrect, answer); 
      }
    }
  }
}