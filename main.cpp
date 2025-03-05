#include<iostream>
#include<fstream>
#include<memory>
#include "parser.cpp"
using namespace std;
int evaluateAST(const ASTNode *node) {
    if (auto numNode = dynamic_cast<const NumberNode*>(node)) {
        return numNode->value;
    }

    if (auto binOpNode = dynamic_cast<const BinaryOpNode*>(node)) {
        int leftValue = evaluateAST(binOpNode->left.get());
        int rightValue = evaluateAST(binOpNode->right.get());

        switch (binOpNode->op) {
            case Token::OPERATOR_PLUS: return leftValue + rightValue;
            case Token::OPERATOR_MINUS: return leftValue - rightValue;
            case Token::OPERATOR_MULTIPLY: return leftValue * rightValue;
            case Token::OPERATOR_DIVIDE: return leftValue / rightValue;
            default: return 0;
        }
    }

    return 0;
}

int main() {
    std::string input = "3 + 5 * (2 - 1)";  // Input expression
    Lexer lexer(input);
    Parser parser(lexer);

    std::unique_ptr<ASTNode> ast = parser.parseExpression();
    if (ast) {
        int result = evaluateAST(ast.get());
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cerr << "Error parsing expression\n";
    }

    return 0;
}
