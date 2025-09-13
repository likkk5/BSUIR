import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class PHPInterpreter {
    private static class Context {
        private final Map<String, Object> variables = new HashMap<>();
        private final Map<String, Object> constants = Map.of("PHP_EOL", "\n");
        private final Map<String, AutoCloseable> resources = new HashMap<>();

        public Object get(String name) {
            if (name.startsWith("$")) {
                if (!variables.containsKey(name)) {
                    throw new RuntimeException("Undefined variable: " + name);
                }
                return variables.get(name);
            } else if (constants.containsKey(name)) {
                return constants.get(name);
            }
            throw new RuntimeException("Unknown identifier: " + name);
        }

        public void set(String name, Object value) {
            variables.put(name, value);
        }

        public String addResource(AutoCloseable resource) {
            String id = "res_" + resources.size();
            resources.put(id, resource);
            return id;
        }

        public AutoCloseable getResource(String id) {
            return resources.get(id);
        }

        public void closeResource(String id) throws Exception {
            AutoCloseable resource = resources.remove(id);
            if (resource != null) {
                resource.close();
            }
        }
    }

    public void interpret(String filename) throws IOException {
        String jsonContent = new String(Files.readAllBytes(Paths.get(filename)));
        Object ast = parseJson(jsonContent);
        interpret(ast, new Context());
    }

    private Object parseJson(String json) {
        json = json.trim();
        if (json.startsWith("{")) {
            return parseJsonObject(json);
        } else if (json.startsWith("[")) {
            return parseJsonArray(json);
        } else if (json.startsWith("\"")) {
            return json.substring(1, json.length() - 1).replace("\\\"", "\"");
        } else if (json.equals("true")) {
            return true;
        } else if (json.equals("false")) {
            return false;
        } else if (json.equals("null")) {
            return null;
        } else if (json.matches("-?\\d+\\.?\\d*")) {
            if (json.contains(".")) {
                return Double.parseDouble(json);
            }
            return Integer.parseInt(json);
        }
        throw new RuntimeException("Invalid JSON value: " + json);
    }

    private Map<String, Object> parseJsonObject(String json) {
        Map<String, Object> result = new HashMap<>();
        json = json.substring(1, json.length() - 1).trim();

        while (!json.isEmpty()) {
            int colonPos = json.indexOf(':');
            String key = json.substring(0, colonPos).trim();
            key = key.startsWith("\"") ? key.substring(1, key.length() - 1) : key;

            json = json.substring(colonPos + 1).trim();
            int endPos = findJsonValueEnd(json);
            String valueStr = json.substring(0, endPos).trim();
            Object value = parseJson(valueStr);

            result.put(key, value);

            json = json.substring(endPos).trim();
            if (json.startsWith(",")) {
                json = json.substring(1).trim();
            }
        }

        return result;
    }

    private List<Object> parseJsonArray(String json) {
        List<Object> result = new ArrayList<>();
        json = json.substring(1, json.length() - 1).trim();

        while (!json.isEmpty()) {
            int endPos = findJsonValueEnd(json);
            String valueStr = json.substring(0, endPos).trim();
            Object value = parseJson(valueStr);

            result.add(value);

            json = json.substring(endPos).trim();
            if (json.startsWith(",")) {
                json = json.substring(1).trim();
            }
        }

        return result;
    }

    private int findJsonValueEnd(String json) {
        int depth = 0;
        boolean inString = false;

        for (int i = 0; i < json.length(); i++) {
            char c = json.charAt(i);

            if (c == '"' && (i == 0 || json.charAt(i - 1) != '\\')) {
                inString = !inString;
            } else if (!inString) {
                if (c == '{' || c == '[') {
                    depth++;
                } else if (c == '}' || c == ']') {
                    depth--;
                } else if (c == ',' && depth == 0) {
                    return i;
                }
            }

            if (depth < 0) {
                return i;
            }
        }

        return json.length();
    }

    @SuppressWarnings("unchecked")
    private Object interpret(Object node, Context ctx) {
        if (node instanceof Map) {
            Map<String, Object> astNode = (Map<String, Object>) node;
//            System.out.println("[DEBUG] Processing node: " + astNode.get("type"));
        }
        if (node instanceof List) {
            for (Object item : (List<?>) node) {
                interpret(item, ctx);
            }
            return null;
        }

        if (!(node instanceof Map)) {
            return node;
        }

        Map<String, Object> astNode = (Map<String, Object>) node;
        String type = (String) astNode.get("type");

        switch (type) {
            case "Program":
                return interpret(astNode.get("body"), ctx);

            case "assign":
                Object left = astNode.get("left");
                Object rightValue = interpret(astNode.get("right"), ctx);
                handleAssignment(left, rightValue, ctx);
                return null;

            case "id":
                return ctx.get((String) astNode.get("value"));

            case "bool":
            case "int":
            case "float":
            case "string":
            case "null":
                return astNode.get("value");

            case "array":
                return interpretArray(astNode, ctx);

            case "new":
                return handleNew(astNode, ctx);

            case "function_call":
                return handleFunctionCall(astNode, ctx);

            case "method_call":
                return handleMethodCall(astNode, ctx);

            case "var_dump":
                handleVarDump(astNode, ctx);
                return null;

            case "if":
                handleIf(astNode, ctx);
                return null;

            case "echo":
                handleEcho(astNode, ctx);
                return null;

            case "operator":
                return handleOperator(astNode, ctx);

            case "property":
                return astNode.get("value");

            case "block":
                return interpret(astNode.get("body"), ctx);

            case "constant":
                return ctx.get((String) astNode.get("value"));

            case "pair":
                return Map.of(
                        "key", interpret(astNode.get("key"), ctx),
                        "value", interpret(astNode.get("value"), ctx)
                );

            default:
                throw new RuntimeException("Unknown node type: " + type);
        }
    }

    @SuppressWarnings("unchecked")
    private void handleAssignment(Object left, Object rightValue, Context ctx) {
        Map<String, Object> leftNode = (Map<String, Object>) left;
        String leftType = (String) leftNode.get("type");

        if ("id".equals(leftType)) {
            ctx.set((String) leftNode.get("value"), rightValue);
        } else if ("operator".equals(leftType) && "->".equals(leftNode.get("operator"))) {
            Object object = interpret(leftNode.get("object"), ctx);
            String property = (String) interpret(leftNode.get("property"), ctx);

            if (object instanceof Map) {
                ((Map<String, Object>) object).put(property, rightValue);
            } else {
                throw new RuntimeException("Cannot set property on non-object type");
            }
        } else {
            throw new RuntimeException("Invalid left-hand side in assignment");
        }
    }

    @SuppressWarnings("unchecked")
    private Object interpretArray(Map<String, Object> arrayNode, Context ctx) {
        List<Object> elements = new ArrayList<>();
        List<Map<String, Object>> items = (List<Map<String, Object>>) arrayNode.get("elements");

        for (Map<String, Object> item : items) {
            if ("pair".equals(item.get("type"))) {
                Map<String, Object> pair = (Map<String, Object>) interpret(item, ctx);
                elements.add(pair);
            } else {
                elements.add(interpret(item, ctx));
            }
        }

        return elements;
    }

    private Object handleNew(Map<String, Object> newNode, Context ctx) {
        String className = (String) newNode.get("class");

        switch (className) {
            case "stdClass":
                return new HashMap<String, Object>();
            case "SplDoublyLinkedList":
                return new ArrayList<Object>();
            default:
                throw new RuntimeException("Unknown class: " + className);
        }
    }

    @SuppressWarnings("unchecked")
    private Object handleFunctionCall(Map<String, Object> callNode, Context ctx) {
        String functionName = (String) callNode.get("name");
        System.out.println("[EXEC] Calling function: " + functionName);
        List<Map<String, Object>> args = (List<Map<String, Object>>) callNode.get("args");
        List<Object> evaluatedArgs = new ArrayList<>();

        for (Map<String, Object> arg : args) {
            evaluatedArgs.add(interpret(arg, ctx));
        }

        try {
            switch (functionName) {
                case "json_encode":
                    return evaluatedArgs.get(0).toString();
                case "file_put_contents":
                    String filename = (String) evaluatedArgs.get(0);
                    String content = (String) evaluatedArgs.get(1);
                    Files.write(Paths.get(filename), content.getBytes());
                    return true;
                case "fopen":
                    String file = (String) evaluatedArgs.get(0);
                    String mode = (String) evaluatedArgs.get(1);
                    java.io.FileInputStream fis = new java.io.FileInputStream(file);
                    return ctx.addResource(fis);
                case "fread":
                    String resId = (String) evaluatedArgs.get(0);
                    int length = ((Number) evaluatedArgs.get(1)).intValue();
                    java.io.FileInputStream stream = (java.io.FileInputStream) ctx.getResource(resId);
                    byte[] buffer = new byte[length];
                    int bytesRead = stream.read(buffer);
                    return new String(buffer, 0, bytesRead);
                case "filesize":
                    return Files.size(Paths.get((String) evaluatedArgs.get(0)));
                case "fclose":
                    String rid = (String) evaluatedArgs.get(0);
                    ctx.closeResource(rid);
                    return true;
                default:
                    throw new RuntimeException("Unknown function: " + functionName);
            }
        } catch (Exception e) {
            throw new RuntimeException("Error executing function " + functionName + ": " + e.getMessage(), e);
        }
    }

    @SuppressWarnings("unchecked")
    private Object handleMethodCall(Map<String, Object> callNode, Context ctx) {
        Object object = interpret(callNode.get("object"), ctx);
        String methodName = (String) interpret(callNode.get("method"), ctx);
        List<Map<String, Object>> args = (List<Map<String, Object>>) callNode.get("args");
        List<Object> evaluatedArgs = new ArrayList<>();

        for (Map<String, Object> arg : args) {
            evaluatedArgs.add(interpret(arg, ctx));
        }

        if (object instanceof List) {
            List<Object> list = (List<Object>) object;
            switch (methodName) {
                case "push":
                    list.add(evaluatedArgs.get(0));
                    return null;
                default:
                    throw new RuntimeException("Unknown method: " + methodName);
            }
        } else {
            throw new RuntimeException("Method call on non-object type");
        }
    }

    @SuppressWarnings("unchecked")
    private void handleVarDump(Map<String, Object> varDumpNode, Context ctx) {
        List<Map<String, Object>> vars = (List<Map<String, Object>>) varDumpNode.get("args");
        for (Map<String, Object> var : vars) {
            String varName = ((String) var.get("value")).substring(1);
            Object value = interpret(var, ctx);
            System.out.printf("$%s(%s) = %s\n",
                    varName,
                    value != null ? value.getClass().getSimpleName() : "null",
                    formatValue(value));
        }
    }
    private String formatValue(Object value) {
        if (value == null) return "NULL";
        if (value instanceof Map) {
            return formatMap((Map<?, ?>) value);
        }
        if (value instanceof List) {
            return formatList((List<?>) value);
        }
        return value.toString();
    }

    private String formatMap(Map<?, ?> map) {
        StringBuilder sb = new StringBuilder("{");
        for (Map.Entry<?, ?> entry : map.entrySet()) {
            if (sb.length() > 1) sb.append(", ");
            sb.append(entry.getKey()).append("=").append(formatValue(entry.getValue()));
        }
        sb.append("}");
        return sb.toString();
    }

    private String formatList(List<?> list) {
        StringBuilder sb = new StringBuilder("[");
        for (Object item : list) {
            if (sb.length() > 1) sb.append(", ");
            sb.append(formatValue(item));
        }
        sb.append("]");
        return sb.toString();
    }
    @SuppressWarnings("unchecked")
    private void handleIf(Map<String, Object> ifNode, Context ctx) {
        Object condition = interpret(ifNode.get("condition"), ctx);
        boolean conditionResult = condition != null &&
                (!(condition instanceof Boolean) || (Boolean) condition);
        System.out.println("[IF] Condition evaluated to: " + conditionResult);

        if (conditionResult) {
            interpret(ifNode.get("thenBlock"), ctx);
        } else if (ifNode.containsKey("elseBlock")) {
            interpret(ifNode.get("elseBlock"), ctx);
        }
    }


    @SuppressWarnings("unchecked")
    private void handleEcho(Map<String, Object> echoNode, Context ctx) {
        List<Map<String, Object>> args = (List<Map<String, Object>>) echoNode.get("args");
//        System.out.println("[ECHO] Outputting values:");
        for (Map<String, Object> arg : args) {
            Object value = interpret(arg, ctx);
            System.out.print(value != null ? value.toString() : "");
        }
    }

    @SuppressWarnings("unchecked")
    private Object handleOperator(Map<String, Object> opNode, Context ctx) {
        String operator = (String) opNode.get("operator");

        if ("->".equals(operator)) {
            Object object = interpret(opNode.get("object"), ctx);
            String property = (String) interpret(opNode.get("property"), ctx);

            if (object instanceof Map) {
                return ((Map<String, Object>) object).get(property);
            }
            throw new RuntimeException("Cannot access property on non-object type");
        }

        throw new RuntimeException("Unsupported operator: " + operator);
    }

}

public class Main {
    public static void main(String[] args) {
        PHPInterpreter interpreter = new PHPInterpreter();
        try {
            interpreter.interpret("tree.json");
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}