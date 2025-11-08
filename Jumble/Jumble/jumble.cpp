//
//  jumble.cpp
//  Jumble
//
//  Created by Isaac W on 2025-11-08.
//
#include "jumble.h"
JumblePuzzle::JumblePuzzle(const std::string& hidden, const std::string& difficulty) {
    int size_multiplier;
    if (difficulty == "easy"){
        size_multiplier = 2;
    }
    else if (difficulty == "medium"){
        size_multiplier = 3;
    }
    else if (difficulty == "hard"){
        size_multiplier = 4;
    }
    else{
        size_multiplier = 2;
    }
    std::size_t puzzle_dim = hidden.length() * size_multiplier;

    
    puzzle = new char*[puzzle_dim];
    for (int i = 0; i<puzzle_dim; i++){
        puzzle[i] = new char[puzzle_dim];
    }
    
}
