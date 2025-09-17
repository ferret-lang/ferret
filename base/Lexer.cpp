#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Refers to the different kinds of tokens available in the langauge.
// These tokens are then passed to the parser to build an AST.
typedef enum TokenKind {
  // Used to mark the end of the source code.
  TOKEN_EOF,

  // Reserved Words
  TOKEN_FUNCTION,
  TOKEN_RETURN,

  // Represents variable names in the language.
  TOKEN_IDENTIFIER_LITERAL,

  // Represents numbers in the language.
  TOKEN_INTEGER_LITERAL,
  TOKEN_FLOAT_LITERAL,

  // Symbols
  TOKEN_LBRACKET,
  TOKEN_RBRACKET,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_SEMICOLON,
  TOKEN_ARROW,

  // Operators
  TOKEN_PLUS,
  TOKEN_HYPHEN,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_EQUAL,
} TokenKind;

// Used to bind information to the raw source code.
class Token {
private:
  // Diagnostics Information; useful in printing
  // detailed errors to the console.
  size_t line = 0;
  size_t column = 0;

  // Classification information for this token.
  TokenKind kind;
  // Representation of itself in raw source code.
  std::string lexeme;

public:
  // Constructor function for the Token.
  Token(std::string lexeme, const TokenKind kind, const size_t line,
        const size_t column)
      : line(line), column(column), kind(kind), lexeme(std::move(lexeme)) {}

  // Function to get the token kind label.
  static std::string getStringEquivalentForKind(TokenKind kind) {
    switch (kind) {
    case TOKEN_FUNCTION:
      return "TOKEN_FUNCTION";
    case TOKEN_RETURN:
      return "TOKEN_RETURN";
    case TOKEN_EOF:
      return "TOKEN_EOF";
    case TOKEN_ARROW:
      return "TOKEN_ARROW";
    case TOKEN_EQUAL:
      return "TOKEN_EQUAL";
    case TOKEN_FLOAT_LITERAL:
      return "TOKEN_FLOAT_LITERAL";
    case TOKEN_IDENTIFIER_LITERAL:
      return "TOKEN_IDENTIFIER_LITERAL";
    case TOKEN_INTEGER_LITERAL:
      return "TOKEN_ITEGER_LITERAL";
    case TOKEN_HYPHEN:
      return "TOKEN_HYPHEN";
    case TOKEN_LBRACE:
      return "TOKEN_LBRACE";
    case TOKEN_LBRACKET:
      return "TOKEN_LBRACKET";
    case TOKEN_PLUS:
      return "TOKEN_PLUS";
    case TOKEN_RBRACE:
      return "TOKEN_RBRACE";
    case TOKEN_RBRACKET:
      return "TOKEN_RBRACKET";
    case TOKEN_SEMICOLON:
      return "TOKEN_SEMICOLON";
    case TOKEN_SLASH:
      return "TOKEN_SLASH";
    case TOKEN_STAR:
      return "TOKEN_STAR";
    }

    return "TOKEN_UNRECOGNIZED";
  }

  // Function to get the lexeme.
  std::string getLexeme() const { return lexeme; }

  // Function to get the token kind.
  TokenKind getKind() const { return kind; }
  std::string getKindLabel() { return getStringEquivalentForKind(kind); }

  // Functions to get the line and column.
  size_t getLine() { return line; }
  size_t getColumn() { return column; }
};

// Iterates over each character in the source code, and
// based of defined rules tokenizes them into tokens.
class Lexer {
private:
  // Used to figure out the position of the current character
  // in the provided source code.
  size_t lPtr = 0;
  size_t line = 0;
  size_t column = 0;

  // Represents that langauge code.
  std::string sourceCode;
  size_t sourceCodeLength;

  // Contains the token representation of the source code.
  std::vector<std::shared_ptr<Token>> tokens;

  // Helper function that checks if we have reached the end of the file.
  bool haveReachedEOF() const { return lPtr >= sourceCodeLength; }

  // Helper function to get the current character.
  char peek() const {
    if (lPtr >= sourceCodeLength) {
      throw std::out_of_range("\nPointer exceeds the source code length!\n" +
                              std::to_string(lPtr) + ">" +
                              std::to_string(sourceCodeLength));
    }
    return sourceCode[lPtr];
  }

  // Increments the pointers value by 1.
  void incrementPtr() {
    lPtr++;
    column++;
  }

  // Helper function to move to the next character.
  char advance() {
    const char currentCharacter = peek();
    incrementPtr();
    return currentCharacter;
  }

  // Helper function to identify whitespaces and comments.
  bool canBeSkipped() const {
    return peek() == ' ' || peek() == '\t' || peek() == '\r';
  }

  // Helper function to assert if the given character is an alphabet.
  static bool isalpha(const char testCharacter) {
    return std::isalpha(testCharacter) || '_' == testCharacter;
  }

  // Helper function to assert if the given character is alphanumeric.
  static bool isalnum(const char testCharacter) {
    return std::isalnum(testCharacter) || '_' == testCharacter;
  }

  // Helper function to make tokens.
  void appendToken(const std::string &lexeme, const TokenKind kind) {
    const auto token = std::make_shared<Token>(lexeme, kind, line, column);
    tokens.push_back(token);
  }

public:
  // Constructor function for the Lexer.
  explicit Lexer(const std::string &sourceCode)
      : sourceCode(sourceCode), sourceCodeLength(sourceCode.size()) {}

  // Function to tokenize the given source code into tokens.
  std::vector<std::shared_ptr<Token>> tokenize() {
    // Looping over each character in the source code.
    while (!haveReachedEOF()) {
      if (canBeSkipped()) {
        incrementPtr();
        continue;
      }
      // Storing the current position of the lexer.
      const size_t startingPosition = lPtr;
      // Advancing the lexer.
      const char currentCharacter = advance();

      // Asserting if the currentCharacter is a newline.
      if (currentCharacter == '\n') {
        line++;
        column = 0;
        continue;
      }

      // Parsing identifiers and reserved words.
      if (Lexer::isalpha(currentCharacter)) {
        while (Lexer::isalnum(peek())) {
          advance();
        }
        const size_t identifierLength = lPtr - startingPosition;
        const std::string identifierLabel =
            sourceCode.substr(startingPosition, identifierLength);

        if (identifierLabel == "function") {
          appendToken(identifierLabel, TOKEN_FUNCTION);
        } else if (identifierLabel == "return") {
          appendToken(identifierLabel, TOKEN_RETURN);
        } else {
          appendToken(identifierLabel, TOKEN_IDENTIFIER_LITERAL);
        }
        continue;
      }

      if (std::isdigit(currentCharacter)) {
        bool isFloat = false;
        while (std::isdigit(peek()) || peek() == '.') {
          const char testCharacter = advance();
          if (testCharacter == '.') {
            if (isFloat) {
              throw std::invalid_argument(
                  std::string("\nInvalid float literal: Multiple decimal "
                              "points encountered.\n") +
                  ">>>: " +
                  sourceCode.substr(startingPosition, lPtr - startingPosition));
            }
            isFloat = true;
          }
        }
        const size_t numberLength = lPtr - startingPosition;
        const std::string numberLabel =
            sourceCode.substr(startingPosition, numberLength);
        appendToken(numberLabel,
                    isFloat ? TOKEN_FLOAT_LITERAL : TOKEN_INTEGER_LITERAL);
        continue;
      }

      switch (currentCharacter) {
      case '(':
        appendToken("(", TOKEN_LBRACKET);
        continue;
      case ')':
        appendToken(")", TOKEN_RBRACKET);
        continue;
      case '{':
        appendToken("{", TOKEN_LBRACE);
        continue;
      case '}':
        appendToken("}", TOKEN_RBRACE);
        continue;
      case ';':
        appendToken(";", TOKEN_SEMICOLON);
        continue;
      case '+':
        appendToken("+", TOKEN_PLUS);
        continue;
      case '*':
        appendToken("*", TOKEN_STAR);
        continue;
      case '/':
        appendToken("/", TOKEN_SLASH);
        continue;
      case '=':
        appendToken("=", TOKEN_EQUAL);
        continue;
      case '-':
        if (peek() == '>') {
          advance();
          appendToken("->", TOKEN_ARROW);
          continue;
        } else {
          appendToken("-", TOKEN_HYPHEN);
          continue;
        }
      default:
        const std::string context =
            sourceCode.substr(startingPosition, lPtr - startingPosition);
        throw std::invalid_argument(
            "\nUnexpected character encountered at position " +
            std::to_string(startingPosition) +
            "\n>>>: " + (context == " " ? "[space]" : context));
      }
    }

    // Marking the end of the tokens.
    appendToken("\0", TOKEN_EOF);
    return tokens;
  };
};
