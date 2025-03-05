#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <string>

// Token types for arithmetic expressions
enum class Token {
    NUMBER,
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    END,
    UNKNOWN
};

// Token structure
struct TokenData {
    Token type;
    std::string value;
};

// Simple lexer to tokenize arithmetic expressions
class Lexer {
public:
    Lexer(const std::string &input) : inputStream(input), currentChar(input[0]) {}

    // Function to get the next token
    TokenData nextToken() {
        skipWhitespace();

        if (currentChar == '\0') {
            return {Token::END, ""}; // End of input
        }

        if (isdigit(currentChar)) {
            return parseNumber();
        }

        if (currentChar == '+') {
            currentChar = inputStream.get();
            return {Token::OPERATOR_PLUS, "+"};
        }

        if (currentChar == '-') {
            currentChar = inputStream.get();
            return {Token::OPERATOR_MINUS, "-"};
        }

        if (currentChar == '*') {
            currentChar = inputStream.get();
            return {Token::OPERATOR_MULTIPLY, "*"};
        }

        if (currentChar == '/') {
            currentChar = inputStream.get();
            return {Token::OPERATOR_DIVIDE, "/"};
        }

        return {Token::UNKNOWN, std::string(1, currentChar)};
    }

private:
    std::istringstream inputStream;
    char currentChar;

    void skipWhitespace() {
        while (isspace(currentChar)) {
            currentChar = inputStream.get();
        }
    }

    TokenData parseNumber() {
        std::string number;
        while (isdigit(currentChar)) {
            number += currentChar;
            currentChar = inputStream.get();
        }
        return {Token::NUMBER, number};
    }
};
