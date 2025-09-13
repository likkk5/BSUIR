import java.io.*;
import java.util.*;
import java.util.regex.*;

enum TokenType {
    VARIABLE, CONSTANT, KEYWORD, SEPARATOR, OPERATOR, STRING, COMMENT, ERROR, PHP_TAG, WHITESPACE, PROPERTY, INVALIDVAR
}

class Token {
    TokenType type;
    String value;
    int id;
    int lineNumber;
    int position;

    Token(TokenType type, String value, int id, int lineNumber, int position) {
        this.type = type;
        this.value = value;
        this.id = id;
        this.lineNumber = lineNumber;
        this.position = position;
    }

    @Override
    public String toString() {
        return "<" + type + ", " + value + ", ID: " + id + ", Line: " + lineNumber + ", Pos: " + position + ">";
    }
}

public class PHPLexer {
    // Регулярное выражение для поиска различных типов лексем
    private static final Pattern TOKEN_PATTERN = Pattern.compile(
            "(?<VARIABLE>\\$[a-zA-Z_][a-zA-Z0-9_]*)|" + // Переменные
                    "(?<INVALIDVAR>\\$(?![a-zA-Z_])\\w*|\\$[0-9]+[a-zA-Z_][a-zA-Z0-9_]*|\\$[a-zA-Z_][a-zA-Z0-9_]*[^a-zA-Z0-9_#'\\$]+)|" +
                    "->\\s*(?<PROPERTY>[a-zA-Z_][a-zA-Z0-9_]*)|"+ // Свойства объектов
                    "(?<CONSTANT>\\d+(\\.\\d+)?([eE][+-]?\\d+)?|\\.\\d+|\\d+\\.)|" + // Константы
                    "(?<STRING>\"([^\"\\\\]|\\\\.)*\"|'([^'\\\\]|\\\\.)*'|\"[^\"]*|\'[^\']*)|" +
                    "(?<HEREDOC><<<'?([A-Z_][A-Z0-9_]*)'?.*?^\\7;$)|" + // Heredoc
                    "(?<KEYWORD>\\b(__halt_compiler|abstract|and|array|as|break|callable|case|catch|class|clone|const|continue|" +
                    "declare|default|die|do|echo|else|elseif|empty|enddeclare|endfor|endforeach|endif|endswitch|endwhile|" +
                    "eval|exit|extends|final|finally|fn|for|foreach|function|global|goto|if|implements|include|include_once|" +
                    "instanceof|insteadof|interface|isset|list|match|namespace|new|or|print|private|protected|public|" +
                    "readonly|require|require_once|return|static|switch|throw|trait|try|unset|use|var|while|xor|yield|yield from|" +
                    "__CLASS__|__DIR__|__FILE__|__FUNCTION__|__LINE__|__METHOD__|__NAMESPACE__|__TRAIT__|null|true|false)\\b|" +
                    "(var_dump|file_put_contents|fopen|fread|fclose|json_encode|stdClass|SplDoublyLinkedList|push|filesize|PHP_VERSION|PHP_EOL))|" +
                    "(?<COMMENT>#.*|//.*|/\\*([^*]*\\*+([^/*][^*]*\\*+)*)?/?)|" + // Комментарии
                    "(?<OPERATOR>=|\\+|\\-|\\*|/|\\.|=>|->|::|&&|\\|\\||\\?|:|\\+=|-=|\\*=|/=|%=)|" + // Операторы
                    "(?<SEPARATOR>[;{}()\\[\\],]|::|>)|" +
                    "(?<WHITESPACE>\\s+)|" + // Пробелы
                    "(?<ERROR>.)", // Некорректные символы
            Pattern.DOTALL
    );

    //"(?<CHAR_LITERAL>'(\\\\.|[^\\\\'])')|" +   // Символьные литералы (например, 'A')
    private int errorCount = 0;
    private final List<Token> tokens = new ArrayList<>();
    private final Map<String, Integer> variableTable = new HashMap<>();
    private final Map<String, Integer> constantTable = new HashMap<>();
    private final Map<String, Integer> keywordTable = new HashMap<>();
    private final Map<String, Integer> separatorTable = new HashMap<>();
    private final Map<String, Integer> operatorTable = new HashMap<>();
    private final Map<String, Integer> identifierTable = new HashMap<>();
    private int identifierIndex = 1;

    // Новые элементы для добавления ID
    private final Map<String, Integer> tokenIds = new HashMap<>();
    private int nextTokenId = 1;

    private int variableIndex = 1;
    private int constantIndex = 1;
    private int keywordIndex = 1;
    private int separatorIndex = 1;
    private int operatorIndex = 1;

    private boolean hasUnclosedString = false;
    private final Stack<Character> bracketStack = new Stack<>();

    // Метод для создания токенов с ID
    private Token createToken(TokenType type, String value, int lineNumber, int position) {
        if (!tokenIds.containsKey(value)) {
            tokenIds.put(value, nextTokenId++);
        }
        return new Token(type, value, tokenIds.get(value), lineNumber, position);
    }
    private boolean insidePHP = false; // Флаг, который сохраняет состояние между строками

    private String processPHPTags(String line, int lineNumber) {
        StringBuilder result = new StringBuilder();
        int index = 0;

        while (index < line.length()) {
            if (line.startsWith("<?php", index)) {  // Открывающий PHP-тег
                if (insidePHP) {
                    System.out.println("Ошибка: Повторное открытие PHP-тега '<?php' без закрытия предыдущего на строке " + lineNumber);
                    errorCount++;
                }
                tokens.add(createToken(TokenType.PHP_TAG, "<?php", lineNumber, index + 1));
                index += 5;
                insidePHP = true;
            } else if (line.startsWith("?>", index)) {  // Закрывающий PHP-тег
                if (!insidePHP) {
                    System.out.println("Ошибка: Обнаружен закрывающий PHP-тег '?>' без открывающего '<?php' на строке " + lineNumber);
                    errorCount++;
                } else {
                    tokens.add(createToken(TokenType.PHP_TAG, "?>", lineNumber, index + 1));
                    insidePHP = false; // Закрываем PHP-блок
                }
                index += 2;
            } else {
                result.append(line.charAt(index));
                index++;
            }
        }

        return result.toString();
    }

    // Метод должен быть вызван в конце обработки файла
    public void checkUnclosedPHPTags() {
        if (insidePHP) {
            System.out.println("Ошибка: Открытый PHP-тег '<?php' не закрыт в конце файла");
            errorCount++;
        }
    }


    public void analyze(String input) {
        String[] lines = input.split("\n");

        for (int lineNumber = 0; lineNumber < lines.length; lineNumber++) {
            String processedLine = processPHPTags(lines[lineNumber], lineNumber);

            boolean hasError = false;

            Pattern.compile("\\d+,\\d+").matcher(processedLine).replaceAll(""); // Удалить числа с запятой
            {
                Matcher m = Pattern.compile("\\d+,\\d+").matcher(processedLine);
                while (m.find()) {
                    String numberWithComma = m.group();
                    int position = m.start() + 1; // Позиция (начинается с 0, поэтому +1 для удобочитаемости)
                    System.out.println("Ошибка: Вещественные числа должны использовать точку вместо запятой. Найдено '"
                            + numberWithComma + "' на строке " + (lineNumber + 1) + ", позиция " + position);
                    errorCount++;
                }
                hasError = true;
            }


            Matcher matcher = TOKEN_PATTERN.matcher(processedLine);

            while (matcher.find()) {
                int position = matcher.start() + 1;

                if (matcher.group("WHITESPACE") != null) {
                    continue;  // Просто игнорируем пробелы
                }
                if (matcher.group("VARIABLE") != null) {
                    String variable = matcher.group("VARIABLE");

                    tokens.add(createToken(TokenType.VARIABLE, variable, lineNumber + 1, position));
                    identifierTable.putIfAbsent(variable, identifierIndex++);
                }
                else if (matcher.group("INVALIDVAR") != null) {
                    String invalidVar = matcher.group("INVALIDVAR");
                    tokens.add(createToken(TokenType.ERROR, invalidVar, lineNumber + 1, position));
                    System.out.println("Ошибка: Некорректное имя переменной '" + matcher.group("INVALIDVAR") +
                            "' на строке " + (lineNumber + 1) + ", позиция " + position);
                    errorCount++;
                }
                else if (matcher.group("PROPERTY") != null) {
                    String property = matcher.group("PROPERTY");
                    if (!keywordTable.containsKey(property)) { // Исключаем ключевые слова
                        tokens.add(createToken(TokenType.PROPERTY, property, lineNumber + 1, position));
                    }
                } else if (matcher.group("CONSTANT") != null) {
                    String constant = matcher.group("CONSTANT");
                    tokens.add(createToken(TokenType.CONSTANT, constant, lineNumber + 1, position));
                    constantTable.putIfAbsent(constant, constantIndex++);
                } else if (matcher.group("STRING") != null) {
                    String str = matcher.group("STRING");
                    // Проверка на закрытие строки
                    if (str.endsWith("\"") || str.endsWith("'")) {
                        tokens.add(createToken(TokenType.STRING, str, lineNumber + 1, position));
                    } else {
                        System.out.println("Ошибка: Незакрытая строка -> \"" + str +
                                "\" на строке " + (lineNumber + 1) + ", позиция " + position);
                        errorCount++;
                    }
                }
                else if (matcher.group("KEYWORD") != null) {
                    String keyword = matcher.group("KEYWORD");
                    //tokens.add(createToken(TokenType.KEYWORD, keyword));
                    //keywordTable.putIfAbsent(keyword, keywordIndex++);
                    // Проверяем, если это не встроенная функция, а пользовательская
                    if (keyword.equals("function")) {
                        matcher.find(); // Получаем имя функции
                        String functionName = matcher.group();
                        tokens.add(createToken(TokenType.VARIABLE, functionName, lineNumber + 1, position)); // Добавляем как идентификатор
                        identifierTable.putIfAbsent(functionName, identifierIndex++);
                    } else {
                        tokens.add(createToken(TokenType.KEYWORD, keyword, lineNumber + 1, position));
                        keywordTable.putIfAbsent(keyword, keywordIndex++);
                    }
                } else if (matcher.group("OPERATOR") != null) {
                    String operator = matcher.group("OPERATOR");
                    tokens.add(createToken(TokenType.OPERATOR, operator, lineNumber + 1, position));
                    operatorTable.putIfAbsent(operator, operatorIndex++);
                } else if (matcher.group("SEPARATOR") != null) {
                    String separator = matcher.group("SEPARATOR");
                    if (separator.equals("->") && matcher.find() && matcher.group("PROPERTY") != null) {
                        String property = matcher.group("PROPERTY");
                        tokens.add(createToken(TokenType.PROPERTY, property, lineNumber + 1, position));
                    } else {
                        tokens.add(createToken(TokenType.SEPARATOR, separator, lineNumber + 1, position));
                        separatorTable.putIfAbsent(separator, separatorIndex++);
                    }
                    trackBrackets(separator, lineNumber + 1, position);
                } else if (matcher.group("COMMENT") != null) {
                    tokens.add(createToken(TokenType.COMMENT, matcher.group("COMMENT"), lineNumber + 1, position));
                } else if (matcher.group("ERROR") != null) {
                    tokens.add(createToken(TokenType.ERROR, matcher.group("ERROR"), lineNumber + 1, position));
                    System.out.println("Ошибка: Некорректный символ '" + matcher.group("ERROR") +
                            "' на строке " + (lineNumber + 1) + ", позиция " + position);
                    errorCount++;
                }
            }
            checkUnclosedElements(processedLine);
        }

        checkUnclosedPHPTags();

        checkUnclosedElements(input);

        if (hasUnclosedString) {
            System.out.println("Ошибка: Незакрытая строка.");
            errorCount++;
        }

        if (!bracketStack.isEmpty()) {
            System.out.println("Ошибка: Незакрытая скобка '" + bracketStack.peek() + "'");
            errorCount++;
        }

        System.out.println("\nОбщее количество ошибок: " + errorCount);
    }
    private boolean isValidVariable(String variable) {
        if (variable.length() < 2 || variable.charAt(0) != '$') {
            return false;
        }

        // Переменная не может начинаться с цифры
        if (Character.isDigit(variable.charAt(1))) {
            return false;
        }

        // Проверяем, что после символа '$' идет буква или '_'
        char firstChar = variable.charAt(1);
        if (!Character.isLetter(firstChar) && firstChar != '_') {
            return false;
        }

        // Проходим по остальной части имени переменной
        for (int i = 2; i < variable.length(); i++) {
            char c = variable.charAt(i);
            // Разрешаем только буквы, цифры и '_'
            if (!Character.isLetterOrDigit(c) && c != '_') {
                return false;
            }
        }

        // Проверка на недопустимые символы
        if (variable.contains("#") || variable.contains("'")) {
            return false;
        }

        return true;
    }

    private void checkUnclosedElements(String input) {
        // Если в tokens уже есть строки, значит все закрыто правильно
        boolean foundString = tokens.stream().anyMatch(t -> t.type == TokenType.STRING);
        if (foundString) return;  // Прерываем проверку

        Pattern doubleQuotePattern = Pattern.compile("\"([^\"\\\\]*(\\\\.[^\"\\\\]*)*)$", Pattern.MULTILINE);
        Pattern singleQuotePattern = Pattern.compile("'([^'\\\\]*(\\\\.[^'\\\\]*)*)$", Pattern.MULTILINE);
        Pattern commentPattern = Pattern.compile("/\\*.*$", Pattern.DOTALL);

        Matcher doubleQuoteMatcher = doubleQuotePattern.matcher(input);
        Matcher singleQuoteMatcher = singleQuotePattern.matcher(input);
        Matcher commentMatcher = commentPattern.matcher(input);

        if (doubleQuoteMatcher.find()) {
            int line = getLineNumber(input, doubleQuoteMatcher.start());
            System.out.println("Ошибка: Незакрытая строка с двойными кавычками на строке " + line + ".");
            errorCount++;
        }

        if (singleQuoteMatcher.find()) {
            int line = getLineNumber(input, singleQuoteMatcher.start());
            System.out.println("Ошибка: Незакрытая строка с одинарными кавычками на строке " + line + ".");
            errorCount++;
        }

        if (commentMatcher.find() && !input.contains("*/")) {
            int line = getLineNumber(input, commentMatcher.start());
            System.out.println("Ошибка: Незакрытый блок комментария на строке " + line + ".");
            errorCount++;
        }
    }
    // Метод для получения номера строки по индексу символа
    private int getLineNumber(String input, int position) {
        return (int) input.substring(0, position).chars().filter(ch -> ch == '\n').count() + 1;
    }
    private void trackBrackets(String separator, int lineNumber, int position) {
        if (separator.equals("(") || separator.equals("{") || separator.equals("[")) {
            bracketStack.push(separator.charAt(0));
        } else if (separator.equals(")") || separator.equals("}") || separator.equals("]")) {
            if (!bracketStack.isEmpty()) {
                char last = bracketStack.pop();
                if ((separator.equals(")") && last != '(') ||
                        (separator.equals("}") && last != '{') ||
                        (separator.equals("]") && last != '[')) {
                    System.out.println("Ошибка: Несоответствующая скобка '" + separator +
                            "' на строке " + lineNumber + ", позиция " + position);
                }
            } else {
                System.out.println("Ошибка: Лишняя скобка '" + separator +
                        "' на строке " + lineNumber + ", позиция " + position);
            }
        }
    }
    public void printTokens() {
        System.out.println("Токены:");
        tokens.forEach(token -> {
            if (token.type == TokenType.PROPERTY) {
                System.out.println("<PROPERTY, " + token.value + ", ID: " + token.id + ">");
            } else {
                System.out.println(token);
            }
        });
    }

    public void printTables() {
        System.out.println("\nТаблица идентификаторов:");
        identifierTable.forEach((key, value) ->
                System.out.println("<IDENT" + value + ", ID:" + tokenIds.get(key) + "> - " + key));

        System.out.println("\nТаблица констант:");
        constantTable.forEach((key, value) ->
                System.out.println("<CONST" + value + ", ID:" + tokenIds.get(key) + "> - " + key));

        System.out.println("\nТаблица ключевых слов:");
        keywordTable.forEach((key, value) ->
                System.out.println("<KEY" + value + ", ID:" + tokenIds.get(key) + "> - " + key));

        System.out.println("\nТаблица разделителей:");
        separatorTable.forEach((key, value) ->
                System.out.println("<SEP" + value + ", ID:" + tokenIds.get(key) + "> - " + key));

        System.out.println("\nТаблица операторов:");
        operatorTable.forEach((key, value) ->
                System.out.println("<OP" + value + ", ID:" + tokenIds.get(key) + "> - " + key));
    }

    public static void main(String[] args) {
        PHPLexer lexer = new PHPLexer();

        try (BufferedReader reader = new BufferedReader(new FileReader("INPUT.TXT"))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line).append("\n");
            }
            lexer.analyze(content.toString().trim());
        } catch (IOException e) {
            System.err.println("Ошибка чтения файла: " + e.getMessage());
        }

        lexer.printTokens();
        lexer.printTables();
    }
}
