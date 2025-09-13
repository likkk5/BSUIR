import tkinter as tk
from tkinter import ttk, messagebox
import sqlite3
from contextlib import closing

class SQLInjectionDemo:
    def __init__(self, root):
        self.root = root
        self.root.title("SQL Injection Demo")
        self.root.geometry("600x550")
        self.root.resizable(False, False)
        
        # Инициализация БД
        self.conn = sqlite3.connect(':memory:')
        self.create_database()
        
        # Стили
        self.style = ttk.Style()
        self.style.configure('TFrame', background='#f0f0f0')
        self.style.configure('Header.TLabel', font=('Arial', 14), background='#f0f0f0')
        self.style.configure('TButton', font=('Arial', 10))
        
        # GUI элементы
        self.create_widgets()
        
    def create_database(self):
        with closing(self.conn.cursor()) as c:
            c.execute('''CREATE TABLE users (
                        id INTEGER PRIMARY KEY,
                        login TEXT NOT NULL,
                        password TEXT NOT NULL)''')
            c.execute("INSERT INTO users (login, password) VALUES ('admin', 'secret')")
            c.execute("INSERT INTO users (login, password) VALUES ('user', 'qwerty')")
            self.conn.commit()
    
    def create_widgets(self):
        main_frame = ttk.Frame(self.root)
        main_frame.pack(padx=20, pady=20, fill=tk.BOTH, expand=True)
        
        # Заголовок
        header = ttk.Label(main_frame, text="SQL Injection Demo", style='Header.TLabel')
        header.pack(pady=10)
        
        # Режимы работы
        mode_frame = ttk.LabelFrame(main_frame, text="Режим работы")
        mode_frame.pack(pady=10, fill=tk.X)
        
        self.mode_var = tk.StringVar(value='unsafe')
        ttk.Radiobutton(mode_frame, text="Небезопасный режим", variable=self.mode_var,
                       value='unsafe').pack(side=tk.LEFT, padx=5)
        ttk.Radiobutton(mode_frame, text="Безопасный режим", variable=self.mode_var,
                       value='safe').pack(side=tk.LEFT, padx=5)
        
        # Поля ввода
        input_frame = ttk.Frame(main_frame)
        input_frame.pack(pady=10, fill=tk.X)
        
        ttk.Label(input_frame, text="Логин:").grid(row=0, column=0, sticky=tk.W, padx=5)
        self.login_entry = ttk.Entry(input_frame, width=30)
        self.login_entry.grid(row=0, column=1, padx=5)
        
        ttk.Label(input_frame, text="Пароль:").grid(row=1, column=0, sticky=tk.W, padx=5)
        self.password_entry = ttk.Entry(input_frame, width=30, show="*")
        self.password_entry.grid(row=1, column=1, padx=5)
        
        # Кнопка входа
        ttk.Button(main_frame, text="Войти", command=self.on_login).pack(pady=10)
        
        # Вывод запроса
        self.sql_label = ttk.Label(main_frame, text="Выполненный SQL запрос:", wraplength=550)
        self.sql_label.pack(pady=5, anchor=tk.W)
        
        # Результат
        self.result_text = tk.Text(main_frame, height=6, wrap=tk.WORD, bg='#fff', 
                                 font=('Consolas', 10), state=tk.DISABLED)
        self.result_text.pack(pady=10, fill=tk.X)
        
        # Примеры атак
        examples_frame = ttk.LabelFrame(main_frame, text="Примеры для тестирования")
        examples_frame.pack(fill="both", expand=True, pady=10)
        canvas = tk.Canvas(examples_frame,                          
                         highlightthickness=0)
        scrollbar = ttk.Scrollbar(examples_frame, 
                                orient="vertical", 
                                command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas, style='TFrame')
        
        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(
                scrollregion=canvas.bbox("all")
            )
        )

        canvas.create_window((0, 0), 
                           window=scrollable_frame, 
                           anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

        # Упаковка элементов внутри examples_frame
        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

        
        examples = [
            "Нормальный ввод: admin / secret",
            "SQL инъекция: ' OR '1'='1' --",
            "Всегда верный запрос: ' OR 1=1 --",
            "Обход пароля: admin' --",                      
        ]
        
        for ex in examples:
            lbl = ttk.Label(scrollable_frame, 
                  text=ex,
                  padding=(5, 2))  # Добавляем отступы
            lbl.pack(anchor=tk.W, fill="x", padx=5, pady=2)  # Явно указываем заполнение
    
    def on_login(self):
        login = self.login_entry.get()
        password = self.password_entry.get()
        mode = self.mode_var.get()
        
        try:
            if mode == 'unsafe':
                user = self.unsafe_login(login, password)
            else:
                user = self.safe_login(login, password)
                
            self.show_result(user)
            
        except Exception as e:
            messagebox.showerror("Ошибка", str(e))
    
    def unsafe_login(self, login, password):
        query = f"SELECT * FROM users WHERE login = '{login}' AND password = '{password}'"
        self.sql_label.config(text=f"Выполненный SQL запрос: {query}")
        
        with closing(self.conn.cursor()) as c:
            c.execute(query)
            return c.fetchone()
    
    def safe_login(self, login, password):
        query = "SELECT * FROM users WHERE login = ? AND password = ?"
        self.sql_label.config(text=f"Выполненный SQL запрос: {query}")
        
        with closing(self.conn.cursor()) as c:
            c.execute(query, (login, password))
            return c.fetchone()
    
    def show_result(self, user):
        self.result_text.config(state=tk.NORMAL)
        self.result_text.delete(1.0, tk.END)
        
        if user:
            self.result_text.insert(tk.END, "Успешный вход! Найден пользователь:\n\n")
            self.result_text.insert(tk.END, f"ID: {user[0]}\nЛогин: {user[1]}\nПароль: {user[2]}")
            self.result_text.config(bg='#dfffdf')
        else:
            self.result_text.insert(tk.END, "Ошибка входа: неверные учетные данные")
            self.result_text.config(bg='#ffdfdf')
        
        self.result_text.config(state=tk.DISABLED)

if __name__ == "__main__":
    root = tk.Tk()
    app = SQLInjectionDemo(root)
    root.mainloop()