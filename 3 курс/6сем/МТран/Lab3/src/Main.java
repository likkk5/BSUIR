import java.util.*;
import java.io.*;
import java.nio.file.*;

enum TokenType {
    PHP_TAG, COMMENT, VARIABLE, CONSTANT, STRING, KEYWORD,
    OPERATOR, SEPARATOR, PROPERTY, ARROW, DOUBLE_ARROW
}

class Token {
    TokenType type;
    String value;
    int lineNumber;
    int position;
    int length;

    public Token(TokenType type, String value, int lineNumber, int position, int length) {
        this.type = type;
        this.value = value;
        this.lineNumber = lineNumber;
        this.position = position;
        this.length = length;
    }

    @Override
    public String toString() {
        return String.format("Token{type=%s, value='%s', line=%d, pos=%d, len=%d}",
                type, value, lineNumber, position, length);
    }
}
 class SyntaxTreeNode {
    String type;  // Тип узла (decl, assign, id, bool и т.д.)
    String value; // Значение узла (если есть)
    List<SyntaxTreeNode> children = new ArrayList<>();

    public SyntaxTreeNode(String type) {
        this.type = type;
    }

    public SyntaxTreeNode(String type, String value) {
        this.type = type;
        this.value = value;
    }

    public void addChild(SyntaxTreeNode node) {
        children.add(node);
    }

    public String toString() {
        return toStringWithIndent(0);
    }

    private String toStringWithIndent(int indent) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < indent; i++) sb.append("   ");

        sb.append(type);
        if (value != null && !value.isEmpty()) {
            sb.append(": ").append(value);
        }
        sb.append("\n");

        for (SyntaxTreeNode child : children) {
            sb.append(child.toStringWithIndent(indent + 1));
        }
        return sb.toString();
    }
}

class PHPParser {
    private final List<Token> tokens;
    private int current = 0;
    private final List<String> errors = new ArrayList<>();

    public PHPParser(List<Token> tokens) {
        this.tokens = tokens;
    }

    public List<String> getErrors() {
        return errors;
    }

    public SyntaxTreeNode parse() {
        SyntaxTreeNode root = new SyntaxTreeNode("Program");

        while (!isAtEnd()) {
            try {
                if (peek().type == TokenType.PHP_TAG || peek().type == TokenType.COMMENT) {
                    advance();  // просто пропускаем
                    continue;
                }

                root.addChild(parseStatement());
            } catch (ParseError error) {
                errors.add(error.getMessage());
                synchronize();  // чтобы не останавливаться после первой ошибки
            }
        }

        return root;
    }

//    private void synchronize() {
//        // Пропустить текущий токен
//        advance();
//
//        // Ищем начало следующего подходящего выражения
//        while (!isAtEnd()) {
//            Token token = peek();
//
//            // Простые эвристики: начало нового выражения
//            if (token.type == TokenType.KEYWORD ||
//                    token.type == TokenType.VARIABLE ||
//                    (token.type == TokenType.SEPARATOR && token.value.equals(";"))) {
//                return;
//            }
//
//            advance();
//        }
//    }
    private void synchronize() {
        // Пропускаем все токены до конца проблемного выражения
        while (!isAtEnd()) {
            // Останавливаемся на ; или } или начале нового выражения
            if (peek().type == TokenType.SEPARATOR && (peek().value.equals(";") || peek().value.equals("}"))) {
                advance(); // Пропускаем ; или }
                return;
            }

            // Или на ключевом слове (if, echo и т.д.)
            if (peek().type == TokenType.KEYWORD) {
                return;
            }

            advance(); // Пропускаем текущий токен
        }
    }
    private SyntaxTreeNode parseStatement() {
        if (match(TokenType.KEYWORD, "echo")) {
            return parseEchoStatement();
        }
        if (match(TokenType.KEYWORD, "if")) {
            return parseIfStatement();
        }
        if (match(TokenType.KEYWORD, "var_dump")) {
            return parseVarDumpStatement();
        }
        if (match(TokenType.VARIABLE)) {
            return parseVariableStatement();
        }
        if (match(TokenType.KEYWORD)) {
            SyntaxTreeNode call = parseFunctionCall();
            consume(TokenType.SEPARATOR, ";", "Ожидается ';' после вызова функции");
            return call;
        }
        return parseExpressionStatement();
    }

    private SyntaxTreeNode parseEchoStatement() {
        SyntaxTreeNode echoNode = new SyntaxTreeNode("echo");
        do {
            if (match(TokenType.STRING) || match(TokenType.VARIABLE) || match(TokenType.CONSTANT)) {
                echoNode.addChild(new SyntaxTreeNode(previous().value));
            } else if (match(TokenType.KEYWORD, "PHP_EOL")) {
                echoNode.addChild(new SyntaxTreeNode("PHP_EOL"));
            } else if (match(TokenType.OPERATOR, ".")) {
                // Skip concatenation operator
            } else if (match(TokenType.KEYWORD, "fread", "filesize")) {
                echoNode.addChild(parseFunctionCall());
            } else {
                break;
            }
        } while (!isAtEnd() && !peek().value.equals(";"));
        consume(TokenType.SEPARATOR, ";", "Ожидается ';' после echo");
        return echoNode;
    }

    private SyntaxTreeNode parseVarDumpStatement() {
        SyntaxTreeNode varDumpNode = new SyntaxTreeNode("var_dump");
        consume(TokenType.SEPARATOR, "(", "Ожидается '(' после var_dump");
        while (!check(TokenType.SEPARATOR, ")") && !isAtEnd()) {
            varDumpNode.addChild(parseExpression());
            if (!match(TokenType.SEPARATOR, ",")) break;
        }
        consume(TokenType.SEPARATOR, ")", "Ожидается ')' после аргументов");
        consume(TokenType.SEPARATOR, ";", "Ожидается ';' после var_dump");
        return varDumpNode;
    }

    private SyntaxTreeNode parseFunctionCallStatement() {
        SyntaxTreeNode call = parseFunctionCall();
        consume(TokenType.SEPARATOR, ";", "Ожидается ';' после вызова функции");
        return call;
    }

    private SyntaxTreeNode parseIfStatement() {
        SyntaxTreeNode ifNode = new SyntaxTreeNode("if");
        consume(TokenType.SEPARATOR, "(", "Ожидается '(' после 'if'");
        ifNode.addChild(parseExpression());
        consume(TokenType.SEPARATOR, ")", "Ожидается ')' после условия");

        ifNode.addChild(parseBlock());

        if (match(TokenType.KEYWORD, "else")) {
            ifNode.addChild(parseBlock());
        }

        return ifNode;
    }

    private SyntaxTreeNode parseBlock() {
        SyntaxTreeNode block = new SyntaxTreeNode("block");

        if (match(TokenType.SEPARATOR, "{")) {
            while (!check(TokenType.SEPARATOR, "}") && !isAtEnd()) {
                try {
                    block.addChild(parseStatement());
                } catch (ParseError error) {
                    errors.add(error.getMessage());
                    synchronize();  // продвигаемся после ошибки
                }
            }
            consume(TokenType.SEPARATOR, "}", "Ожидается '}' в конце блока");
        } else {
            try {
                block.addChild(parseStatement());
            } catch (ParseError error) {
                errors.add(error.getMessage());
                synchronize();
            }
        }

        return block;
    }


    private SyntaxTreeNode parseVariableStatement() {
        Token variable = previous();
        SyntaxTreeNode left = new SyntaxTreeNode("id", variable.value);

        left = parsePropertyAccess(left);

        if (match(TokenType.OPERATOR, "=")) {
            SyntaxTreeNode assignment = new SyntaxTreeNode("assign", "=");
            assignment.addChild(left);
            assignment.addChild(parseExpression());
            consume(TokenType.SEPARATOR, ";", "Ожидается ';' после выражения");
            return assignment;
        }

        consume(TokenType.SEPARATOR, ";", "Ожидается ';' после выражения");
        return left;
    }

    private SyntaxTreeNode parsePropertyAccess(SyntaxTreeNode object) {
        while (match(TokenType.OPERATOR, "->")) {
            SyntaxTreeNode propAccess = new SyntaxTreeNode("operator", "->");
            propAccess.addChild(object);

            if (match(TokenType.PROPERTY) || match(TokenType.KEYWORD)) {
                propAccess.addChild(new SyntaxTreeNode("property", previous().value));
                object = propAccess;

                if (!isAtEnd() && peek().type == TokenType.OPERATOR && peek().value.equals("=")) {
                    return object;
                }

                if (match(TokenType.SEPARATOR, "(")) {
                    object = parseMethodCall(object);
                }
            } else {
                throw error(peek(), "Ожидается имя свойства после ->");
            }
        }
        return object;
    }

    private SyntaxTreeNode parseMethodCall(SyntaxTreeNode object) {
        SyntaxTreeNode callNode = new SyntaxTreeNode("method_call");
        callNode.addChild(object);

        while (!check(TokenType.SEPARATOR, ")") && !isAtEnd()) {
            callNode.addChild(parseExpression());
            if (!match(TokenType.SEPARATOR, ",")) break;
        }

        consume(TokenType.SEPARATOR, ")", "Ожидается ')' после аргументов метода");
        return callNode;
    }

    private SyntaxTreeNode parseExpressionStatement() {
        SyntaxTreeNode expr = parseExpression();
        consume(TokenType.SEPARATOR, ";", "Ожидается ';' после выражения");
        SyntaxTreeNode stmt = new SyntaxTreeNode("expr_stmt");
        stmt.addChild(expr);
        return stmt;
    }

    private SyntaxTreeNode parseExpression() {
        return parseAssignment();
    }

    private SyntaxTreeNode parseAssignment() {
        SyntaxTreeNode expr = parseLogicalOr();

        if (match(TokenType.OPERATOR, "=")) {
            SyntaxTreeNode assignment = new SyntaxTreeNode("=");
            assignment.addChild(expr);
            assignment.addChild(parseAssignment());
            return assignment;
        }

        return expr;
    }

    private SyntaxTreeNode parseLogicalOr() {
        SyntaxTreeNode node = parseLogicalAnd();

        while (match(TokenType.OPERATOR, "||")) {
            SyntaxTreeNode newNode = new SyntaxTreeNode("||");
            newNode.addChild(node);
            newNode.addChild(parseLogicalAnd());
            node = newNode;
        }

        return node;
    }

    private SyntaxTreeNode parseLogicalAnd() {
        SyntaxTreeNode node = parseEquality();

        while (match(TokenType.OPERATOR, "&&")) {
            SyntaxTreeNode newNode = new SyntaxTreeNode("&&");
            newNode.addChild(node);
            newNode.addChild(parseEquality());
            node = newNode;
        }

        return node;
    }

    private SyntaxTreeNode parseEquality() {
        SyntaxTreeNode node = parseComparison();

        while (match(TokenType.OPERATOR, "==", "!=")) {
            SyntaxTreeNode newNode = new SyntaxTreeNode(previous().value);
            newNode.addChild(node);
            newNode.addChild(parseComparison());
            node = newNode;
        }

        return node;
    }

    private SyntaxTreeNode parseComparison() {
        SyntaxTreeNode node = parseAdditive();

        while (match(TokenType.OPERATOR, "<", "<=", ">", ">=")) {
            SyntaxTreeNode newNode = new SyntaxTreeNode(previous().value);
            newNode.addChild(node);
            newNode.addChild(parseAdditive());
            node = newNode;
        }

        return node;
    }

    private SyntaxTreeNode parseAdditive() {
        SyntaxTreeNode node = parseMultiplicative();

        while (match(TokenType.OPERATOR, "+", "-")) {


            SyntaxTreeNode newNode = new SyntaxTreeNode(previous().value);
            newNode.addChild(node);
            newNode.addChild(parseMultiplicative());
            node = newNode;
        }
        if (peek().type == TokenType.OPERATOR &&
                !List.of("+", "-", "*", "/", "%", "=>").contains(peek().value)) {

            if (peek().value.equals("@")) {
                throw error(peek(), "Оператор '@' не может использоваться как бинарный оператор.");
            } else {
                throw error(peek(), "Недопустимый оператор '" + peek().value + "' между выражениями.");
            }
        }

        return node;
    }

    private SyntaxTreeNode parseMultiplicative() {
        SyntaxTreeNode node = parsePrimary();

        while (match(TokenType.OPERATOR, "*", "/", "%")) {

            SyntaxTreeNode newNode = new SyntaxTreeNode(previous().value);
            newNode.addChild(node);
            newNode.addChild(parsePrimary());
            node = newNode;
        }
        if (peek().type == TokenType.OPERATOR &&
                !List.of("+", "-", "*", "/", "%", "=>").contains(peek().value)) {

            if (peek().value.equals("@")) {
                throw error(peek(), "Оператор '@' не может использоваться как бинарный оператор.");
            } else {
                throw error(peek(), "Недопустимый оператор '" + peek().value + "' между выражениями.");
            }
        }

        return node;
    }

    private SyntaxTreeNode parsePrimary() {
        if (match(TokenType.OPERATOR, "@")) {
            throw error(previous(), "Оператор @ может использоваться только для подавления ошибок, а не как бинарный оператор");
        }
        if (match(TokenType.VARIABLE)) {
            SyntaxTreeNode varNode = new SyntaxTreeNode("id", previous().value);
            if (peek().type == TokenType.OPERATOR && peek().value.equals("->")) {
                return parsePropertyAccess(varNode);
            }
            return varNode;
        }
        if (match(TokenType.CONSTANT)) {
            // Определяем тип константы (целое, дробное)
            String value = previous().value;
            String type = value.contains(".") ? "float" : "int";
            return new SyntaxTreeNode(type, value);
        }
        if (match(TokenType.STRING)) {
            return new SyntaxTreeNode("string", previous().value);
        }
        if (match(TokenType.KEYWORD, "true", "false")) {
            return new SyntaxTreeNode("bool", previous().value);
        }
        if (match(TokenType.KEYWORD, "null")) {
            return new SyntaxTreeNode("null", previous().value);
        }
        if (match(TokenType.SEPARATOR, "(")) {
            SyntaxTreeNode node = new SyntaxTreeNode("group");
            node.addChild(parseExpression());
            consume(TokenType.SEPARATOR, ")", "Ожидается ')' после выражения");
            return node;
        }
        if (match(TokenType.SEPARATOR, "[")) {
            return parseArray();
        }
        if (match(TokenType.KEYWORD, "new")) {
            return parseNewExpression();
        }
        if (match(TokenType.KEYWORD)) {
            return parseFunctionCall();
        }

        throw error(peek(), "Ожидается первичное выражение");
    }
    private SyntaxTreeNode parseArray() {
        SyntaxTreeNode arrayNode = new SyntaxTreeNode("array");
        while (!check(TokenType.SEPARATOR, "]") && !isAtEnd()) {
            SyntaxTreeNode key = parseExpression();

            if (match(TokenType.OPERATOR, "=>")) {
                SyntaxTreeNode pair = new SyntaxTreeNode("pair");
                pair.addChild(key);
                pair.addChild(parseExpression());
                arrayNode.addChild(pair);
            } else {
                arrayNode.addChild(key);
            }

            if (!match(TokenType.SEPARATOR, ",")) break;
        }
        consume(TokenType.SEPARATOR, "]", "Ожидается ']' после элементов массива");
        return arrayNode;
    }

    private SyntaxTreeNode parseNewExpression() {
        SyntaxTreeNode newNode = new SyntaxTreeNode("new");
        Token className = consume(TokenType.KEYWORD, "Ожидается имя класса после 'new'");
        newNode.addChild(new SyntaxTreeNode(className.value));

        if (match(TokenType.SEPARATOR, "(")) {
            SyntaxTreeNode args = new SyntaxTreeNode("args");
            while (!check(TokenType.SEPARATOR, ")") && !isAtEnd()) {
                args.addChild(parseExpression());
                if (!match(TokenType.SEPARATOR, ",")) break;
            }
            newNode.addChild(args);
            consume(TokenType.SEPARATOR, ")", "Ожидается ')' после аргументов конструктора");
        }

        return newNode;
    }

    private SyntaxTreeNode parseFunctionCall() {
        Token funcName = previous();
        SyntaxTreeNode callNode = new SyntaxTreeNode("function_call");
        callNode.addChild(new SyntaxTreeNode(funcName.value));

        consume(TokenType.SEPARATOR, "(", "Ожидается '(' после имени функции");
        while (!check(TokenType.SEPARATOR, ")") && !isAtEnd()) {
            callNode.addChild(parseExpression());
            if (!match(TokenType.SEPARATOR, ",")) break;
        }
        consume(TokenType.SEPARATOR, ")", "Ожидается ')' после аргументов");

        return callNode;
    }

    // Вспомогательные методы
    private boolean match(TokenType type, String... values) {
        if (check(type)) {
            if (values.length == 0) {
                advance();
                return true;
            }
            for (String value : values) {
                if (peek().value.equals(value)) {
                    advance();
                    return true;
                }
            }
        }
        return false;
    }

    private Token consume(TokenType type, String message) {
        if (check(type)) return advance();
        throw error(peek(), message);
    }

    private Token consume(TokenType type, String value, String message) {
        if (check(type, value)) return advance();
        throw error(peek(), message);
    }

    private ParseError error(Token token, String message) {
        return new ParseError(String.format("[Line %d, Pos %d] Error: %s",
                token.lineNumber, token.position, message));
    }

    private boolean isAtEnd() {
        return current >= tokens.size();
    }

    private Token peek() {
        return tokens.get(current);
    }

    private Token previous() {
        return tokens.get(current - 1);
    }

    private Token advance() {
        if (!isAtEnd()) current++;
        return previous();
    }

    private boolean check(TokenType type) {
        return !isAtEnd() && peek().type == type;
    }

    private boolean check(TokenType type, String value) {
        return !isAtEnd() && peek().type == type && peek().value.equals(value);
    }
}

class ParseError extends RuntimeException {
    public ParseError(String message) {
        super(message);
    }
}
public class Main {
    public static void main(String[] args) {
        // 1. Создаем список токенов напрямую в коде
        List<Token> tokens = createTokensList();

        // 2. Создание и запуск парсера
        PHPParser parser = new PHPParser(tokens);
        SyntaxTreeNode syntaxTree = parser.parse();

        saveSyntaxTreeToFile(syntaxTree, "syntax_tree.txt");

        // 3. Вывод результатов
        System.out.println("Синтаксическое дерево:");
        System.out.println(syntaxTree);

        System.out.println("\nОшибки синтаксического анализа:");
        parser.getErrors().forEach(System.out::println);
    }
    private static void saveSyntaxTreeToFile(SyntaxTreeNode syntaxTree, String filename) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            writer.write(syntaxTree.toString());
            System.out.println("Синтаксическое дерево сохранено в файл: " + filename);
        } catch (IOException e) {
            System.err.println("Ошибка при сохранении дерева в файл: " + e.getMessage());
        }
    }
    private static List<Token> createTokensList() {
        List<Token> tokens = new ArrayList<>();

        // Основные токены
        tokens.add(new Token(TokenType.PHP_TAG, "<?php", 0, 1, 5));
        tokens.add(new Token(TokenType.COMMENT, "// 1. Типы переменных и структуры данных", 2, 1, 38));

        // Простые присваивания
        tokens.add(new Token(TokenType.VARIABLE, "$boolVar", 3, 1, 8));
        tokens.add(new Token(TokenType.OPERATOR, "=", 3, 10, 1));
        tokens.add(new Token(TokenType.KEYWORD, "true", 3, 12, 4));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 3, 16, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$charVar", 4, 1, 8));
        tokens.add(new Token(TokenType.OPERATOR, "=", 4, 10, 1));
        tokens.add(new Token(TokenType.STRING, "'A'", 4, 12, 3));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 4, 15, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$intVar", 5, 1, 7));
        tokens.add(new Token(TokenType.OPERATOR, "=", 5, 9, 1));
        tokens.add(new Token(TokenType.CONSTANT, "10", 5, 11, 2));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 5, 13, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$floatVar", 6, 1, 9));
        tokens.add(new Token(TokenType.OPERATOR, "=", 6, 11, 1));
        tokens.add(new Token(TokenType.CONSTANT, "3.14", 6, 13, 4));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 6, 17, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$stringVar", 7, 1, 10));
        tokens.add(new Token(TokenType.OPERATOR, "=", 7, 12, 1));
        tokens.add(new Token(TokenType.STRING, "\"Hello, PHP!\"", 7, 14, 13));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 7, 27, 1));

        // Массив
        tokens.add(new Token(TokenType.VARIABLE, "$arrayVar", 8, 1, 9));
        tokens.add(new Token(TokenType.OPERATOR, "=", 8, 11, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "[", 8, 13, 1));
        tokens.add(new Token(TokenType.CONSTANT, "1", 8, 14, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 8, 15, 1));
        tokens.add(new Token(TokenType.CONSTANT, "2", 8, 17, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 8, 18, 1));
        tokens.add(new Token(TokenType.CONSTANT, "3", 8, 20, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "]", 8, 21, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 8, 22, 1));

        // Ассоциативный массив
        tokens.add(new Token(TokenType.VARIABLE, "$assocArray", 9, 1, 11));
        tokens.add(new Token(TokenType.OPERATOR, "=", 9, 13, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "[", 9, 15, 1));
        tokens.add(new Token(TokenType.STRING, "\"key\"", 9, 16, 5));
        tokens.add(new Token(TokenType.OPERATOR, "=>", 9, 22, 2));
        tokens.add(new Token(TokenType.STRING, "\"value\"", 9, 25, 7));
        tokens.add(new Token(TokenType.SEPARATOR, "]", 9, 32, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 9, 33, 1));

        // Объекты
        tokens.add(new Token(TokenType.VARIABLE, "$obj", 10, 1, 4));
        tokens.add(new Token(TokenType.OPERATOR, "=", 10, 6, 1));
        tokens.add(new Token(TokenType.KEYWORD, "new", 10, 8, 3));
        tokens.add(new Token(TokenType.KEYWORD, "stdClass", 10, 12, 8));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 10, 20, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 10, 21, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 10, 22, 1));

        // Свойство объекта
        tokens.add(new Token(TokenType.VARIABLE, "$obj", 11, 1, 4));
        tokens.add(new Token(TokenType.OPERATOR, "->", 11, 5, 2));
        tokens.add(new Token(TokenType.PROPERTY, "name", 11, 7, 4));
        tokens.add(new Token(TokenType.OPERATOR, "=", 11, 12, 1));
        tokens.add(new Token(TokenType.STRING, "\"John\"", 11, 14, 6));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 11, 20, 1));

        // JSON encode
        tokens.add(new Token(TokenType.VARIABLE, "$json", 12, 1, 5));
        tokens.add(new Token(TokenType.OPERATOR, "=", 12, 7, 1));
        tokens.add(new Token(TokenType.KEYWORD, "json_encode", 12, 9, 11));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 12, 20, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$arrayVar", 12, 21, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 12, 30, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 12, 31, 1));

        // LinkedList
        tokens.add(new Token(TokenType.VARIABLE, "$linkedList", 13, 1, 11));
        tokens.add(new Token(TokenType.OPERATOR, "=", 13, 13, 1));
        tokens.add(new Token(TokenType.KEYWORD, "new", 13, 15, 3));
        tokens.add(new Token(TokenType.KEYWORD, "SplDoublyLinkedList", 13, 19, 19));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 13, 38, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 13, 39, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 13, 40, 1));

        // Методы LinkedList
        tokens.add(new Token(TokenType.VARIABLE, "$linkedList", 14, 1, 11));
        tokens.add(new Token(TokenType.OPERATOR, "->", 14, 12, 2));
        tokens.add(new Token(TokenType.PROPERTY, "push", 14, 14, 4));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 14, 18, 1));
        tokens.add(new Token(TokenType.CONSTANT, "10", 14, 19, 2));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 14, 21, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 14, 22, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$linkedList", 15, 1, 11));
        tokens.add(new Token(TokenType.OPERATOR, "->", 15, 12, 2));
        tokens.add(new Token(TokenType.PROPERTY, "push", 15, 14, 4));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 15, 18, 1));
        tokens.add(new Token(TokenType.CONSTANT, "20", 15, 19, 2));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 15, 21, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 15, 22, 1));

        // Null
        tokens.add(new Token(TokenType.VARIABLE, "$nullVar", 16, 1, 8));
        tokens.add(new Token(TokenType.OPERATOR, "=", 16, 10, 1));
        tokens.add(new Token(TokenType.KEYWORD, "null", 16, 12, 4));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 16, 16, 1));

        // Комментарии
        tokens.add(new Token(TokenType.COMMENT, "//$123invalidVar = \"Ошибка\";", 18, 1, 27));
        tokens.add(new Token(TokenType.COMMENT, "//$unterminatedString = \"Hello, PHP!;", 19, 1, 36));
        tokens.add(new Token(TokenType.COMMENT, "// Работа с файлом", 21, 1, 18));

        // Работа с файлами
        tokens.add(new Token(TokenType.VARIABLE, "$filename", 22, 1, 9));
        tokens.add(new Token(TokenType.OPERATOR, "=", 22, 11, 1));
        tokens.add(new Token(TokenType.STRING, "\"file.txt\"", 22, 13, 10));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 22, 23, 1));

        tokens.add(new Token(TokenType.KEYWORD, "file_put_contents", 23, 1, 17));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 23, 18, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$filename", 23, 19, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 23, 28, 1));
        tokens.add(new Token(TokenType.STRING, "\"Sample text inside file.\"", 23, 30, 26));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 23, 56, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 23, 57, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$resourceVar", 24, 1, 12));
        tokens.add(new Token(TokenType.OPERATOR, "=", 24, 14, 1));
        tokens.add(new Token(TokenType.KEYWORD, "fopen", 24, 16, 5));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 24, 21, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$filename", 24, 22, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 24, 31, 1));
        tokens.add(new Token(TokenType.STRING, "\"r\"", 24, 33, 3));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 24, 36, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 24, 37, 1));

        // Вывод переменных
        tokens.add(new Token(TokenType.COMMENT, "// Вывод переменных", 26, 1, 18));

        tokens.add(new Token(TokenType.KEYWORD, "var_dump", 27, 1, 8));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 27, 9, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$boolVar", 27, 10, 8));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 18, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$charVar", 27, 20, 8));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 28, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$intVar", 27, 30, 7));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 37, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$floatVar", 27, 39, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 48, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$stringVar", 27, 50, 10));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 60, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$arrayVar", 27, 62, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 71, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$assocArray", 27, 73, 11));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 84, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$obj", 27, 86, 4));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 90, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$json", 27, 92, 5));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 97, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$linkedList", 27, 99, 11));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 110, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$nullVar", 27, 112, 8));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 27, 120, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$resourceVar", 27, 122, 12));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 27, 134, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 27, 135, 1));

        // Чтение файла
        tokens.add(new Token(TokenType.COMMENT, "// Читаем и выводим содержимое файла", 29, 1, 36));

        tokens.add(new Token(TokenType.KEYWORD, "if", 30, 1, 2));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 30, 4, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$resourceVar", 30, 5, 12));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 30, 17, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "{", 30, 19, 1));

        tokens.add(new Token(TokenType.KEYWORD, "echo", 31, 5, 4));
        tokens.add(new Token(TokenType.STRING, "\"File Content: \"", 31, 10, 16));
        tokens.add(new Token(TokenType.OPERATOR, ".", 31, 27, 1));
        tokens.add(new Token(TokenType.KEYWORD, "fread", 31, 29, 5));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 31, 34, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$resourceVar", 31, 35, 12));
        tokens.add(new Token(TokenType.SEPARATOR, ",", 31, 47, 1));
        tokens.add(new Token(TokenType.KEYWORD, "filesize", 31, 49, 8));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 31, 57, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$filename", 31, 58, 9));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 31, 67, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 31, 68, 1));
        tokens.add(new Token(TokenType.OPERATOR, ".", 31, 70, 1));
        tokens.add(new Token(TokenType.KEYWORD, "PHP_EOL", 31, 72, 7));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 31, 79, 1));

        tokens.add(new Token(TokenType.KEYWORD, "fclose", 32, 5, 6));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 32, 11, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$resourceVar", 32, 12, 12));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 32, 24, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 32, 25, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "}", 33, 1, 1));

        // Else блок
        tokens.add(new Token(TokenType.KEYWORD, "else", 33, 3, 4));
        tokens.add(new Token(TokenType.SEPARATOR, "{", 33, 8, 1));

        tokens.add(new Token(TokenType.KEYWORD, "echo", 34, 5, 4));
        tokens.add(new Token(TokenType.STRING, "\"Ошибка открытия файла!\"", 34, 10, 24));
        tokens.add(new Token(TokenType.OPERATOR, ".", 34, 35, 1));
        tokens.add(new Token(TokenType.KEYWORD, "PHP_EOL", 34, 37, 7));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 34, 44, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "}", 35, 1, 1));

        // Завершение
        tokens.add(new Token(TokenType.KEYWORD, "echo", 37, 1, 4));
        tokens.add(new Token(TokenType.KEYWORD, "PHP_EOL", 37, 6, 7));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 37, 13, 1));
        tokens.add(new Token(TokenType.PHP_TAG, "?>", 37, 1, 2));

        tokens.add(new Token(TokenType.VARIABLE, "$badArray", 38, 1, 9));
        tokens.add(new Token(TokenType.OPERATOR, "=", 38, 11, 1));
        tokens.add(new Token(TokenType.SEPARATOR, "[", 38, 13, 1));
        tokens.add(new Token(TokenType.CONSTANT, "1", 38, 14, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ")", 38, 15, 1)); // Ошибка: ) вместо ]
        tokens.add(new Token(TokenType.SEPARATOR, ";", 38, 16, 1));

        // Нет закрывающей скобки и точки с запятой
        tokens.add(new Token(TokenType.KEYWORD, "var_dump", 39, 1, 8));
        tokens.add(new Token(TokenType.SEPARATOR, "(", 39, 9, 1));
        tokens.add(new Token(TokenType.VARIABLE, "$intVar", 39, 10, 7));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 39, 11, 1));

        tokens.add(new Token(TokenType.VARIABLE, "$a", 40, 1, 2));
        tokens.add(new Token(TokenType.OPERATOR, "=", 40, 3, 1));
        tokens.add(new Token(TokenType.CONSTANT, "5", 40, 5, 1));
        tokens.add(new Token(TokenType.OPERATOR, "@", 40, 7, 1));
        tokens.add(new Token(TokenType.CONSTANT, "3", 40, 9, 1));
        tokens.add(new Token(TokenType.SEPARATOR, ";", 40, 10, 1));

        return tokens;
    }
}