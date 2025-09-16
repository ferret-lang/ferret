#include "Lexer.cpp"
#include <memory>
#include <variant>

// AST refers to Abstract Syntax Tree,
// all the nodes in this tree represent a specific statement.
typedef enum ASTKind {
  // All other nodes would be encapsulated inside this node,
  // and this nodes must be at the top of the tree.
  TRANSLATION_UNIT,
} ASTKind;

// Forward declaration of ASTNode.
struct ASTNode;

typedef struct TranslationUnit {
  std::vector<std::shared_ptr<ASTNode>> declarations;
} TranslationUnit;
typedef struct ASTNode {
  std::variant<std::shared_ptr<TranslationUnit>> as;
} ASTNode;

// Creates an overall structure for the program
// using the tokens created by Lexer.
class Parser {
private:
  // Variable that stores the current token index.
  int lPtr = 0;
  std::vector<std::shared_ptr<Token>> tokens;

  // Helper function to retrieve the current token.
  std::shared_ptr<Token> peek() { return tokens[lPtr]; }

  // Helper function to assert the EOF.
  bool isEOF() {
    if (peek()->getKind() == TOKEN_EOF) {
      return true;
    }
    return false;
  }

  // Helper function to advance the token index.
  void advance() { lPtr++; }

  // Helper function to check if the current token matches the expected type.
  bool match(TokenKind type) {
    if (peek()->getKind() == type) {
      advance();
      return true;
    }
    return false;
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
      std::cout << peek()->getLexeme() << std::endl;
      advance();
    }

    // Building a node.
    auto node = std::make_shared<ASTNode>();
    node->as = translationUnit;
    return node;
  }

  // Function to print the AST.
  static void print(std::shared_ptr<ASTNode> node) {
    std::cout << "Pending Implementation" << std::endl;
  }
};
