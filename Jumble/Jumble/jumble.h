//
//  jumble.h
//  Jumble
//
//  Created by Isaac W on 2025-11-08.
//
#include <string>
#include <iostream>
#include <ctime>
class JumblePuzzle {
private:
    char** puzzle;
    
    
public:
JumblePuzzle(const std::string& hidden, const std::string& difficulty);
JumblePuzzle(JumblePuzzle& jb);
};
