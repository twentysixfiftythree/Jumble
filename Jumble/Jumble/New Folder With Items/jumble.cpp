//
//  jumble.cpp
//  Jumble
//
//  Created by Isaac W on 2025-11-08.
//

#include "jumble.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>  // helper for lowercase
#include <cctype>     // for std::tolower


void JumblePuzzle::insertWord() {
    bool fits = false;
    //  goes until it finds a way to fit the word
    while (!fits) {
        direction = "nesw"[rand() % 4];
        row = rand() % puzzle_dim;
        col = rand() % puzzle_dim;
        fits = true;

        switch (direction) {
            case 'n': if (row - wordLen + 1 < 0) fits = false; break;
            case 's': if (row + wordLen > puzzle_dim) fits = false; break;
            case 'e': if (col + wordLen > puzzle_dim) fits = false; break;
            case 'w': if (col - wordLen + 1 < 0) fits = false; break;
        }
    }
    // inserts the word
    for (int i = 0; i < wordLen; i++) {
        switch (direction) {
            case 'n': jumble[row - i][col] = hidden_word[i]; break;
            case 's': jumble[row + i][col] = hidden_word[i]; break;
            case 'e': jumble[row][col + i] = hidden_word[i]; break;
            case 'w': jumble[row][col - i] = hidden_word[i]; break;
        }
    }
}




JumblePuzzle::JumblePuzzle(const std::string& hidden, const std::string& difficulty)
    : wordLen(hidden.length())
{
    // check hidden word length
    if (wordLen < 3 || wordLen > 10)
        throw BadJumbleException("Hidden word must be between 3 and 10 characters.");

    // Convert hidden word to lowercase
    hidden_word = hidden;
    std::transform(hidden_word.begin(), hidden_word.end(), hidden_word.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // convert difficulty to lowercase
    std::string diff = difficulty;
    std::transform(diff.begin(), diff.end(), diff.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Validate difficulty
    int size_multiplier;
    if (diff == "easy") size_multiplier = 2;
    else if (diff == "medium") size_multiplier = 3;
    else if (diff == "hard") size_multiplier = 4;
    else
        throw BadJumbleException("Difficulty must be 'easy', 'medium', or 'hard'.");

    puzzle_dim = static_cast<int>(wordLen) * size_multiplier;

    // Allocate 2D array
    jumble = new charArrayPtr[puzzle_dim];
    for (int i = 0; i < puzzle_dim; i++)
        jumble[i] = new char[puzzle_dim];

    // Fill with random lowercase letters
    srand(static_cast<unsigned int>(time(nullptr)));
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < puzzle_dim; i++)
        for (int j = 0; j < puzzle_dim; j++)
            jumble[i][j] = letters[rand() % 26];

    insertWord();
}


JumblePuzzle::~JumblePuzzle() {
    for (int i = 0; i < puzzle_dim; i++)
        delete[] jumble[i];
    delete[] jumble;
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& other)
    : hidden_word(other.hidden_word),
      wordLen(other.wordLen),
      puzzle_dim(other.puzzle_dim),
      row(other.row),
      col(other.col),
      direction(other.direction)
{
    // Deep copy of 2D array
    jumble = new charArrayPtr[puzzle_dim];
    for (int i = 0; i < puzzle_dim; i++) {
        jumble[i] = new char[puzzle_dim];
        for (int j = 0; j < puzzle_dim; j++)
            jumble[i][j] = other.jumble[i][j];
    }
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& other) {
    if (this != &other) {
        // Delete old 2D array
        for (int i = 0; i < puzzle_dim; i++)
            delete[] jumble[i];
        delete[] jumble;

        // Copy scalar fields
        hidden_word = other.hidden_word;
        wordLen = other.wordLen;
        puzzle_dim = other.puzzle_dim;
        row = other.row;
        col = other.col;
        direction = other.direction;

        // Deep copy new 2D array
        jumble = new charArrayPtr[puzzle_dim];
        for (int i = 0; i < puzzle_dim; i++) {
            jumble[i] = new char[puzzle_dim];
            for (int j = 0; j < puzzle_dim; j++)
                jumble[i][j] = other.jumble[i][j];
        }
    }
    return *this;
}

// getters
int JumblePuzzle::getSize() const { return puzzle_dim; }
int JumblePuzzle::getRowPos() const { return row; }
int JumblePuzzle::getColPos() const { return col; }
char JumblePuzzle::getDirection() const { return direction; }
charArrayPtr* JumblePuzzle::getJumble() const { return jumble; }
