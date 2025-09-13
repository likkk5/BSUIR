import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

class SyntaxTreeNode {
    String type;
    String value;
    List<SyntaxTreeNode> children = new ArrayList<>();
    SyntaxTreeNode parent;  // Добавлено поле для хранения родителя

    public SyntaxTreeNode(String type) {
        this.type = type;
    }

    public SyntaxTreeNode(String type, String value) {
        this.type = type;
        this.value = value;
    }

    // Метод для добавления дочернего узла и установки родителя
    public void addChild(SyntaxTreeNode node) {
        node.parent = this;  // Устанавливаем родителя для дочернего узла
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

class SyntaxTreeReader {
    public static SyntaxTreeNode readFromFile(String filename) {
        List<String> lines = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = reader.readLine()) != null) {
                lines.add(line);
            }
        } catch (IOException e) {
            System.err.println("Ошибка при чтении файла: " + e.getMessage());
            return null;
        }
        return buildTreeFromLines(lines);
    }

    private static SyntaxTreeNode buildTreeFromLines(List<String> lines) {
        if (lines.isEmpty()) return null;
        SyntaxTreeNode root = parseLine(lines.get(0));
        buildTreeRecursive(root, lines, 1, 0);
        return root;
    }

    private static int buildTreeRecursive(SyntaxTreeNode parent, List<String> lines, int index, int parentIndent) {
        while (index < lines.size()) {
            String line = lines.get(index);
            int currentIndent = countIndent(line);
            if (currentIndent <= parentIndent) return index;
            if (currentIndent == parentIndent + 1) {
                SyntaxTreeNode node = parseLine(line.trim());
                parent.addChild(node);
                index = buildTreeRecursive(node, lines, index + 1, currentIndent);
            } else {
                index++;
            }
        }
        return index;
    }

    private static int countIndent(String line) {
        int count = 0;
        while (count < line.length() && line.charAt(count) == ' ') {
            count++;
        }
        return count / 3;
    }

    private static SyntaxTreeNode parseLine(String line) {
        if (line.contains(": ")) {
            String[] parts = line.split(": ", 2);
            return new SyntaxTreeNode(parts[0], parts[1]);
        } else {
            return new SyntaxTreeNode(line);
        }
    }
}

class SemanticAnalyzer {
    private final SyntaxTreeNode syntaxTree;
    private final List<String> errors = new ArrayList<>();
    private final Map<String, VariableInfo> symbolTable = new HashMap<>();
    private final Stack<Map<String, VariableInfo>> scopeStack = new Stack<>();

    public SemanticAnalyzer(SyntaxTreeNode syntaxTree) {
        this.syntaxTree = syntaxTree;
        initializeBuiltInTypes();
    }

    private void initializeBuiltInTypes() {
        symbolTable.put("true", new VariableInfo("bool", true));
        symbolTable.put("false", new VariableInfo("bool", true));
        symbolTable.put("null", new VariableInfo("null", true));
        symbolTable.put("PHP_EOL", new VariableInfo("string", true));
        symbolTable.put("stdClass", new VariableInfo("class", true));
        symbolTable.put("SplDoublyLinkedList", new VariableInfo("class", true));
        symbolTable.put("array", new VariableInfo("array", true));
        symbolTable.put("resource", new VariableInfo("resource", true));
    }

    public List<String> analyze() {
        scopeStack.push(new HashMap<>());
        analyzeNode(syntaxTree);
        return errors;
    }

    private void analyzeNode(SyntaxTreeNode node) {
        System.out.println("Анализ узла: " + node.type + (node.value != null ? " со значением " + node.value : ""));
        switch (node.type) {
            case "Program": analyzeProgram(node); break;
            case "assign": analyzeAssignment(node); break;
            case "id": checkVariableExists(node.value); break;
            case "call": analyzeFunctionCall(node); break;
            case "method_call": analyzeMethodCall(node); break;
            case "operator": analyzeOperator(node); break;
            case "if": analyzeIfStatement(node); break;
            case "echo": analyzeEchoStatement(node); break;
            case "var_dump": analyzeVarDump(node); break;
            case "new": analyzeNewExpression(node); break;
            case "array": case "pair": case "property":
                node.children.forEach(this::analyzeNode); break;
            default: node.children.forEach(this::analyzeNode);
        }
    }

    private void analyzeProgram(SyntaxTreeNode programNode) {
        enterScope();
        programNode.children.forEach(this::analyzeNode);
        exitScope();
    }


    private void analyzeAssignment(SyntaxTreeNode assignNode) {
        if (assignNode.children.size() < 2) return;
        SyntaxTreeNode left = assignNode.children.get(0);
        SyntaxTreeNode right = assignNode.children.get(1);
        analyzeNode(right);
        String rightType = inferType(right);

        // Специальная обработка null
        if (rightType.equals("null")) {
            rightType = "mixed";  // null может быть присвоен любому типу
        }

        if (left.type.equals("id")) {
            String varName = left.value;

            // Проверка переменной в текущем скоупе
            Map<String, VariableInfo> currentScope = scopeStack.peek();
            VariableInfo localVar = currentScope.get(varName);

            if (localVar != null) {
                // Повторное объявление в том же скоупе: проверяем тип
                if (!isTypeCompatible(localVar.type, rightType)) {
                    errors.add(String.format("Ошибка типа: нельзя присвоить значение типа '%s' переменной '%s' типа '%s' в той же области видимости",
                            rightType, varName, localVar.type));
                }
            } else {
                // Внешняя переменная или новая — разрешено
                currentScope.put(varName, new VariableInfo(rightType, false));
            }

        } else if (left.type.equals("operator") && left.value.equals("->")) {
            analyzeNode(left);
        }
    }

    private VariableInfo lookupVariable(String name) {
        for (int i = scopeStack.size() - 1; i >= 0; i--) {
            Map<String, VariableInfo> scope = scopeStack.get(i);
            if (scope.containsKey(name)) {
                return scope.get(name);
            }
        }
        return null;
    }


    private void analyzeFunctionCall(SyntaxTreeNode callNode) {
        if (callNode.children.isEmpty()) return;
        String functionName = callNode.children.get(0).value;
        if (callNode.children.size() > 1) {
            callNode.children.get(1).children.forEach(this::analyzeNode);
        }
        if (!isBuiltInFunction(functionName)) {
            errors.add("Неизвестная функция: " + functionName);
        }
    }

    private void analyzeMethodCall(SyntaxTreeNode methodCallNode) {
        if (methodCallNode.children.size() < 2) return;
        SyntaxTreeNode objectNode = methodCallNode.children.get(0);
        analyzeNode(objectNode);
        String objectType = inferType(objectNode);
//
        if (!objectType.equals("object") && !objectType.equals("mixed") && !objectType.equals("class")) {
            errors.add("Вызов метода не у объекта: " + objectType);
        }
        if (methodCallNode.children.size() > 2) {
            analyzeNode(methodCallNode.children.get(2));
        }
    }

    private void analyzeOperator(SyntaxTreeNode operatorNode) {
        String operator = operatorNode.value;
        operatorNode.children.forEach(this::analyzeNode);

        if (operatorNode.children.isEmpty()) return;

        // Обработка унарных операторов
        if (operatorNode.children.size() == 1) {
            String operandType = inferType(operatorNode.children.get(0));
            if (operator.equals("!") && !operandType.equals("bool")) {
                errors.add("Операнд оператора ! должен быть boolean, получен: " + operandType);
            }
            return;
        }

        // Обработка бинарных операторов
        if (operatorNode.children.size() == 2) {
            String leftType = inferType(operatorNode.children.get(0));
            String rightType = inferType(operatorNode.children.get(1));

            if (operator.equals("->")) {
                // Разрешаем -> для объектов, классов и mixed типов
                if (!leftType.equals("object") && !leftType.equals("class") && !leftType.equals("mixed")) {
                    errors.add("Оператор -> применяется к не объекту: " + leftType);
                }
            } else if (operator.equals(".")) {
                // Оператор конкатенации разрешен для любых типов
                // PHP автоматически преобразует их в строки
                return;
            } else if (!isOperationValid(operator, leftType, rightType)) {
                errors.add(String.format("Недопустимая операция: %s между %s и %s",
                        operator, leftType, rightType));
            }
        }
    }

    private void analyzeIfStatement(SyntaxTreeNode ifNode) {
        if (ifNode.children.isEmpty()) return;
        analyzeNode(ifNode.children.get(0));

        // Создаем новую область видимости, копируя текущие переменные
        enterScope();
        // Копируем переменные из родительской области видимости
        if (!scopeStack.isEmpty()) {
            scopeStack.peek().forEach((name, info) ->
                    scopeStack.peek().put(name, new VariableInfo(info.type, info.isConstant)));
        }

        if (ifNode.children.size() > 1) analyzeNode(ifNode.children.get(1));
        exitScope();

        if (ifNode.children.size() > 2) {
            enterScope();
            // Копируем переменные из родительской области видимости
            if (!scopeStack.isEmpty()) {
                scopeStack.peek().forEach((name, info) ->
                        scopeStack.peek().put(name, new VariableInfo(info.type, info.isConstant)));
            }
            analyzeNode(ifNode.children.get(2));
            exitScope();
        }
    }

    private void analyzeEchoStatement(SyntaxTreeNode echoNode) {
        echoNode.children.forEach(child -> {
            analyzeNode(child);
            String type = inferType(child);
            // Добавляем "null" и "mixed" в разрешённые типы
            if (!type.equals("string") && !type.equals("int") && !type.equals("float") &&
                    !type.equals("bool") && !type.equals("null") && !type.equals("mixed") &&
                    !type.equals("array") && !type.equals("resource")) {
                errors.add("Недопустимый тип для echo: " + type);
            }
        });
    }


    private void analyzeVarDump(SyntaxTreeNode varDumpNode) {
        varDumpNode.children.forEach(this::analyzeNode);
    }

    private void analyzeNewExpression(SyntaxTreeNode newNode) {
        if (newNode.children.isEmpty()) {
            errors.add("Ошибка: выражение 'new' без указания класса");
            return;
        }

        SyntaxTreeNode classNode = newNode.children.get(0);

        String className = classNode.value != null ? classNode.value : classNode.type;

        if (className == null || className.isEmpty()) {
            errors.add("Не удалось определить имя класса при создании объекта");
            return;
        }

        if ("null".equalsIgnoreCase(className)) {
            errors.add("Нельзя создать экземпляр null");
            return;
        }

        if (!symbolTable.containsKey(className)) {
            errors.add("Неизвестный класс: " + className);
        }
    }


    private String inferType(SyntaxTreeNode node) {
       System.out.println("Анализ типа: " + node.type + " value: " + node.value);
        switch (node.type) {
            case "id":
                VariableInfo varInfo = lookupVariable(node.value);
                return varInfo != null ? varInfo.type : "unknown";
            case "null":
                if (node.parent != null && node.parent.type.equals("assign")) {
                    return "null"; // Если это присваивание, то null - это тип
                }
                return "null_value"; // В других случаях это значение null
            case "int":
                return "int";
            case "float":
                return "float";
            case "string":
                return "string";
            case "bool":
                return "bool";
            case "new":
                return "object";
            case "array":
                return "array";
            case "operator":
            case "call":
            case "method_call":
                return inferExpressionType(node);
            case "property":
                return "mixed";
            case "resource":
                return "resource";
            default:
                return "mixed";
        }
    }


    private String inferExpressionType(SyntaxTreeNode node) {
        if (node.type.equals("operator")) {
            String operator = node.value;
            String leftType = inferType(node.children.get(0));
            if (node.children.size() == 1) return leftType;
            String rightType = inferType(node.children.get(1));

            switch (operator) {
                case "+": case "-": case "*": case "/":
                    return leftType.equals("float") || rightType.equals("float") ? "float" : "int";
                case "&&": case "||": case "!":
                    return "bool";
                case "==": case "!=": case ">": case "<": case ">=": case "<=":
                    return "bool";
                case ".":
                    return "string";
                case "->":
                    // Для оператора -> возвращаем mixed, так как тип метода неизвестен
                    return "mixed";
                default:
                    return "unknown";
            }
        } else if (node.type.equals("call")) {
            // Обработка вызовов функций
            if (node.children.isEmpty()) return "unknown";

            String functionName = node.children.get(0).value;

            // Добавляем известные возвращаемые типы для встроенных функций
            switch (functionName) {
                case "fread": case "file_get_contents":
                    return "string";
                case "filesize":
                    return "int";
                case "fopen":
                    return "resource";
                case "fclose":
                    return "bool";
                case "json_encode":
                    return "string";
                case "count": case "sizeof":
                    return "int";
                case "strlen":
                    return "int";
                default:
                    // Для неизвестных функций возвращаем mixed
                    return "mixed";
            }
        } else if (node.type.equals("method_call")) {
            // Для вызовов методов всегда возвращаем mixed,
            // так как без информации о классе точный тип неизвестен
            return "mixed";
        }
        return "unknown";
    }

    private boolean isOperationValid(String operator, String leftType, String rightType) {
        switch (operator) {
            case "+": case "-": case "*": case "/":
                return isNumeric(leftType) && isNumeric(rightType);
            case "&&": case "||":
                return leftType.equals("bool") && rightType.equals("bool");
            case "==": case "!=": case ">": case "<": case ">=": case "<=":
                return isNumeric(leftType) && isNumeric(rightType);
            case ".": return true;
            default: return false;
        }
    }

    private boolean isTypeCompatible(String targetType, String sourceType) {
        if (sourceType.equals("null")) return true;
        return targetType.equals(sourceType) || targetType.equals("mixed") ||
                (isNumeric(targetType) && isNumeric(sourceType));
    }

    private boolean isNumeric(String type) {
        return type.equals("int") || type.equals("float");
    }

    private boolean isBuiltInFunction(String name) {
        return Set.of("echo", "print", "var_dump", "isset", "empty", "count", "sizeof",
                "strlen", "array", "json_encode", "fopen", "fclose", "fread",
                "filesize", "file_put_contents").contains(name);
    }

    private void checkVariableExists(String varName) {
        // Проверяем сначала в текущей области видимости, затем в родительских
        for (int i = scopeStack.size() - 1; i >= 0; i--) {
            if (scopeStack.get(i).containsKey(varName)) {
                return;
            }
        }

        // Проверяем в глобальных символах
        if (!symbolTable.containsKey(varName)) {
            errors.add("Необъявленная переменная: " + varName);
        }
    }

    private void enterScope() {
        System.out.println("Вход в новую область видимости");
        scopeStack.push(new HashMap<>());
    }

    private void exitScope() {
        if (scopeStack.size() > 1) scopeStack.pop();
    }

    private static class VariableInfo {
        String type;
        boolean isConstant;
        VariableInfo(String type, boolean isConstant) {
            this.type = type;
            this.isConstant = isConstant;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        analyzeFile("C:\\Users\\lishy\\IdeaProjects\\Lab4_mtran\\syntax_tree.txt", "Основной файл");
        analyzeFile("C:\\Users\\lishy\\IdeaProjects\\Lab4_mtran\\syntax_tree_errors.txt", "Файл с ошибками");
    }

    private static void analyzeFile(String path, String label) {
        System.out.println("==== " + label + " ====");
        SyntaxTreeNode syntaxTree = SyntaxTreeReader.readFromFile(path);
        if (syntaxTree == null) {
            System.err.println("Не удалось прочитать " + label);
            return;
        }
        System.out.println("Прочитанное синтаксическое дерево:");
        System.out.println(syntaxTree);
        SemanticAnalyzer analyzer = new SemanticAnalyzer(syntaxTree);
        List<String> semanticErrors = analyzer.analyze();
        System.out.println("\nСемантические ошибки:");
        if (semanticErrors.isEmpty()) {
            System.out.println("Ошибок не найдено.");
        } else {
            semanticErrors.forEach(System.out::println);
        }
        System.out.println();
    }
}
