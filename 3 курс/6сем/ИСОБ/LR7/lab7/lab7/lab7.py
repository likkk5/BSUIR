#coding: windows-1251
import ast
import astor
import base64
import random
import string

builtins_dir = dir(__builtins__)
reserved = {
    'decode', 'base64', 'exec', 'compile', 's', '__builtins__',
    'ast', 'astor', 'base64', 'random', 'string'
}
builtins_list = {"print", "range", "len", "int", "float", "str", "bool"}

class RenameVisitor(ast.NodeTransformer):
    def __init__(self):
        self.var_map = {}
        self.func_map = {}
        self.current_params = set()

    def visit_ClassDef(self, node):
        if node.name not in reserved and not node.name.startswith('__'):
            new_name = self._generate_name()
            self.func_map[node.name] = new_name
            node.name = new_name
        return self.generic_visit(node)

    def visit_FunctionDef(self, node):
        if node.name not in reserved and not node.name.startswith('__'):
            new_name = self._generate_name()
            self.func_map[node.name] = new_name
            node.name = new_name

        original_params = [param.arg for param in node.args.args]
        new_params = [self._generate_name() for _ in node.args.args]
        
        for old, new in zip(original_params, new_params):
            self.var_map[old] = new
            self.current_params.add(new)

        node.args.args = [ast.arg(arg=name) for name in new_params]
        return self.generic_visit(node)

    
    def visit_Name(self, node):
        if node.id in self.func_map:
            node.id = self.func_map[node.id]
        elif node.id in self.var_map:
            node.id = self.var_map[node.id]
        elif node.id == "__name__":  
            return node
        elif node.id in builtins_list:  
            return node
        elif (node.id not in builtins_dir and 
              node.id not in reserved and 
              node.id not in self.current_params):
            new_name = self._generate_name()
            self.var_map[node.id] = new_name
            node.id = new_name
        return node

    def _generate_name(self):
        return ''.join(random.choices(string.ascii_letters, k=16))

    def visit_Compare(self, node):

        if (isinstance(node.left, ast.Name) and node.left.id == "__name__" and
            isinstance(node.comparators[0], ast.Constant) and node.comparators[0].value == "__main__"):
            return node 
        return self.generic_visit(node)

class StringObfuscator(ast.NodeTransformer):
    def visit_JoinedStr(self, node):
        return node
    
    def visit_Str(self, node):
        if isinstance(node.parent, ast.JoinedStr):
            return node
        encoded = base64.b64encode(node.value.encode()).decode()
        return ast.Call(
            func=ast.Name(id='decode', ctx=ast.Load()),
            args=[ast.Constant(value=encoded)],
            keywords=[]
        )

def obfuscate(source: str) -> str:
    decoder_ast = ast.parse("""
import base64
def decode(s):
    return base64.b64decode(s).decode()
""")
    
    main_ast = ast.parse(source)
    
    for node in ast.walk(main_ast):
        for child in ast.iter_child_nodes(node):
            child.parent = node
    
    full_ast = ast.Module(body=decoder_ast.body + main_ast.body)
    
    transformer = RenameVisitor()
    full_ast = transformer.visit(full_ast)
    full_ast = StringObfuscator().visit(full_ast)
    ast.fix_missing_locations(full_ast)
    
    return astor.to_source(full_ast)

if __name__ == "__main__":
    try:
        with open('input_code.py', 'r', encoding='utf-8') as f:
            original_code = f.read()
        
        obfuscated_code = obfuscate(original_code)
        
        with open('output.py', 'w', encoding='utf-8') as f:
            f.write(obfuscated_code)
        
        print("Код успешно прошел обфускацию. Преобразованный код в output.py")
    
    except FileNotFoundError:
        print("Ошибка: Файл input_code.py не найден")
