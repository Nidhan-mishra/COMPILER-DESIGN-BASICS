#include <iostream>
#include <memory>
#include <string>
#include "lexer.cpp"
// Abstract Syntax Tree (AST) for arithmetic expressions
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode {
public:
    int value;
    NumberNode(int val) : value(val) {}
};

class BinaryOpNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    Token op;

    BinaryOpNode(std::unique_ptr<ASTNode> left, Token op, std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};

// Simple parser for arithmetic expressions
class Parser {
public:
    Parser(Lexer &lexer) : lexer(lexer), currentToken(lexer.nextToken()) {}

    std::unique_ptr<ASTNode> parseExpression() {
        return parseAdditionSubtraction();
    }

private:
    Lexer &lexer;
    TokenData currentToken;

    void advance() {
        currentToken = lexer.nextToken();
    }

    std::unique_ptr<ASTNode> parseAdditionSubtraction() {
        std::unique_ptr<ASTNode> node = parseMultiplicationDivision();

        while (currentToken.type == Token::OPERATOR_PLUS || currentToken.type == Token::OPERATOR_MINUS) {
            Token op = currentToken.type;
            advance(); // Consume the operator

            std::unique_ptr<ASTNode> right = parseMultiplicationDivision();
            node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
        }

        return node;
    }

    std::unique_ptr<ASTNode> parseMultiplicationDivision() {
        std::unique_ptr<ASTNode> node = parsePrimary();

        while (currentToken.type == Token::OPERATOR_MULTIPLY || currentToken.type == Token::OPERATOR_DIVIDE) {
            Token op = currentToken.type;
            advance(); // Consume the operator

            std::unique_ptr<ASTNode> right = parsePrimary();
            node = std::make_unique<BinaryOpNode>(std::move(node), op, std::move(right));
        }

        return node;
    }

    std::unique_ptr<ASTNode> parsePrimary() {
        if (currentToken.type == Token::NUMBER) {
            int value = std::stoi(currentToken.value);
            advance(); // Consume the number
            return std::make_unique<NumberNode>(value);
        }

        std::cerr << "Error: Expected number\n";
        return nullptr;
    }
};
