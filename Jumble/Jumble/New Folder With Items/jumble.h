//
//  jumble.h
//  Jumble
//
//  Created by Isaac W on 2025-11-08.
//



#include <string>
#include <iostream>
#include <exception>

typedef char* charArrayPtr;


class BadJumbleException : public std::exception {
private:
    std::string message;
public:
    BadJumbleException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};


class JumblePuzzle {
private:
    charArrayPtr* jumble;   // 2D array stored on heap
    int puzzle_dim;
    std::size_t wordLen;
    std::string hidden_word;
    int row;
    int col;
    char direction;

    void insertWord();      // helper to insert the hidden word

public:
    // big three
    JumblePuzzle(const std::string& hidden, const std::string& difficulty);
    JumblePuzzle(const JumblePuzzle& other);
    JumblePuzzle& operator=(const JumblePuzzle& other);
    ~JumblePuzzle();

    // getters
    int getSize() const;
    int getRowPos() const;
    int getColPos() const;
    char getDirection() const;
    charArrayPtr* getJumble() const;

};
