#include <string>
#include <any>
#include <string>
#include <utility>   

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  END_OF_FILE
};

std::string toString(TokenType type) {
  static const std::string strings[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
    "BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",
    "IDENTIFIER", "STRING", "NUMBER",
    "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR",
    "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",
    "END_OF_FILE"
  };

  return strings[static_cast<int>(type)];
}

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const std::any literal;
  const int line;

  Token(TokenType type, std::string lexeme, std::any literal,
        int line)
    : type{type}, lexeme{std::move(lexeme)},
      literal{std::move(literal)}, line{line}
  {}

  std::string toString() const {
    std::string literal_text;

    switch (type) {
      case (IDENTIFIER):
        literal_text = lexeme;
        break;
      case (STRING):
        literal_text = std::any_cast<std::string>(literal);
        break;
      case (NUMBER):
        literal_text = std::to_string(std::any_cast<double>(literal));
        break;
      case (TRUE):
        literal_text = "true";
        break;
      case (FALSE):
        literal_text = "false";
        break;
      default:
        literal_text = "nil";
    }

    return ::toString(type) + " " + lexeme + " " + literal_text;
  }
};