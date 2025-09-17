#include "Lexer.cpp"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>

// Defining the size of tab in spaces,
// used while printing the AST to the console.
const size_t tabSize = 4;

// AST refers to Abstract Syntax Tree,
// all the nodes in this tree represent a specific statement.
typedef enum ASTKind {
  // All other nodes would be encapsulated inside this node,
  // and this nodes must be at the top of the tree.
  TRANSLATION_UNIT,

  // Used for defining functions.
  AST_FUNCTION_DECLARATION
} ASTKind;

// Forward declaration of ASTNode.
struct ASTNode;

// TODO: Implement parameters and blocks.
typedef struct FunctionDeclaration {
  std::string fnReturnType;
  std::string fnName;
  std::vector<std::shared_ptr<ASTNode>> fnParameters;
  std::shared_ptr<ASTNode> fnBlock;
} FunctionDeclaration;
typedef struct TranslationUnit {
  std::vector<std::shared_ptr<ASTNode>> declarations;
} TranslationUnit;
typedef struct ASTNode {
  ASTKind kind;
  std::variant<std::shared_ptr<TranslationUnit>,
               std::shared_ptr<FunctionDeclaration>>
      as;
} ASTNode;

// Creates an overall structure for the program
// using the tokens created by Lexer.
class Parser {
private:
  // Variable that stores the current token index.
  int lPtr = 0;
  std::vector<std::shared_ptr<Token>> tokens;

  // Helper function to retrieve the current token.
  std::shared_ptr<Token> peek() const { return tokens[lPtr]; }

  // Helper function to assert the EOF.
  bool isEOF() const {
    if (peek()->getKind() == TOKEN_EOF) {
      return true;
    }
    return false;
  }

  // Helper function to advance the token index.
  std::shared_ptr<Token> advance() {
    auto currentToken = peek();
    lPtr++;
    return currentToken;
  }

  // Helper function to check if the current token matches the expected type.
  bool compare(TokenKind kind) const { return peek()->getKind() == kind; }

  // Helper function to check the current token and advance.
  void skipIf(TokenKind kind) {
    if (!compare(kind)) {
      throw std::invalid_argument(std::string("\nExpected a ") +
                                  Token::getStringEquivalentForKind(kind) +
                                  " but found: " + peek()->getKindLabel());
    }

    advance();
  }

  // Helper function to parse function declarations.
  // In Ferret, only types and functions can be declared globally.
  std::shared_ptr<ASTNode> parse_declaration() {
    if (compare(TOKEN_IDENTIFIER_LITERAL)) {
      auto fnReturnType = advance();
      auto fnIdentifierLabel = advance();

      skipIf(TOKEN_LBRACKET);
      // TODO: Parse parameters
      skipIf(TOKEN_RBRACKET);

      skipIf(TOKEN_LBRACE);
      while (!compare(TOKEN_RBRACE)) {
        // TODO: Parse block
        advance();
      }
      skipIf(TOKEN_RBRACE);

      auto functionDeclaration = std::make_shared<FunctionDeclaration>();
      functionDeclaration->fnReturnType = fnReturnType->getLexeme();
      functionDeclaration->fnName = fnIdentifierLabel->getLexeme();
      functionDeclaration->fnParameters = {};
      functionDeclaration->fnBlock = nullptr;

      auto node = std::make_shared<ASTNode>();
      node->kind = AST_FUNCTION_DECLARATION;
      node->as = functionDeclaration;

      return node;
    }

    // Throw an error if the declaration is not a function.
    throw std::invalid_argument(
        std::string("\nExpected a function declaration, but found: ") +
        peek()->getKindLabel());
  }

public:
  // Constructor function for the Parser.
  explicit Parser(const std::string &sourceCode)
      : tokens(std::make_shared<Lexer>(sourceCode)->tokenize()) {}

  // Function to generate an AST from the tokens.
  std::shared_ptr<ASTNode> generateTranslationUnit() {
    // Building the HEAD node.
    auto translationUnit = std::make_shared<TranslationUnit>();
    translationUnit->declarations = {};

    // Looping over the tokens.
    while (!isEOF()) {
      auto declaration = parse_declaration();
      translationUnit->declarations.push_back(declaration);
    }

    // Building a node.
    auto node = std::make_shared<ASTNode>();
    node->kind = TRANSLATION_UNIT;
    node->as = translationUnit;
    return node;
  }

  // Function to print the AST.
  static void print(std::shared_ptr<ASTNode> node, size_t indent = 0) {
    switch (node->kind) {
    case TRANSLATION_UNIT: {
      std::cout << std::string(indent, ' ') << "TRANSLATION_UNIT" << std::endl;
      auto translationUnit =
          std::get<std::shared_ptr<TranslationUnit>>(node->as);
      for (auto &declaration : translationUnit->declarations) {
        print(declaration, indent + tabSize);
      }
    }; break;
    case AST_FUNCTION_DECLARATION: {
      std::cout << std::string(indent, ' ') << "FUNCTION_DECLARATION"
                << std::endl;
    }; break;
    }
  }
};
