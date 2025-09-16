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

typedef struct TranslationUnit {} TranslationUnit;
typedef struct ASTNode {
  std::variant<
    std::shared_ptr<TranslationUnit>
  > as;
} ASTNode;

// Creates an overall structure for the program
// using the tokens created by Lexer.
class Parser {
private:
  std::shared_ptr<Lexer> lexer;

public:
  // Constructor function for the Parser.
  explicit Parser(const std::string &sourceCode) : lexer(std::make_shared<Lexer>(sourceCode)) {
  }

  // Function to generate an AST from the tokens.
  std::shared_ptr<ASTNode> generateTranslationUnit() {
    // Creating tokens from the source code.
    auto tokens = lexer->tokenize();

    // Building the HEAD node.
    auto translationUnit = std::make_shared<TranslationUnit>();

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
