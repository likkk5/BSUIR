# -*- coding: windows-1251 -*-
import argparse

def generate_html_table(rows=300, cols=5):
    # Input validation
    if not isinstance(rows, int) or not isinstance(cols, int):
        raise ValueError("Rows and columns must be integers")
    if rows <= 0 or cols <= 0:
        raise ValueError("Rows and columns must be greater than 0")
    
    if rows <= 1:
        color_step = 0  # ���� ���� ������, ���� �� ����������
    else:
        color_step = 299 // (rows - 1)  # ��� ��� ��������� �����
    
    # ������ HTML-���������
    html = """
    <html>
    <head>
        <title>Gradient Table</title>
        <style>
            table {
                border-collapse: collapse;
                width: 100%;
            }
            td {
                padding: 10px;
                text-align: center;
                border: 1px solid black;
            }
        </style>
    </head>
    <body>
        <table>
    """

    # ��������� ����� �������
    for i in range(rows):
        # ��������� ���� ��� ������� ������
        color_value = 255 - i * color_step
        color_value = max(0, color_value)  # ����� �� ���� ������������� ��������
        color = f'rgb({color_value}, {color_value}, {color_value})'  # ���� �� ������ � �������
        html += f'<tr style="background-color: {color};">\n'
        
        # ��������� �������� ��� ������
        for j in range(cols):
            html += f'<td>Row {i+1}, Col {j+1}</td>\n'
        
        html += '</tr>\n'

    # ���������� HTML-���������
    html += """
        </table>
    </body>
    </html>
    """

    # ������ � ����
    with open('gradient_table.html', 'w') as file:
        file.write(html)

    print("HTML ���� 'gradient_table.html' ������� ������.")

    return html 

def main():
    # ������� ������ ����������
    parser = argparse.ArgumentParser(description="Generate an HTML table with gradient rows.")
    parser.add_argument("rows", type=int, default=300, help="Number of rows in the table")
    parser.add_argument("cols", type=int, default=5, help="Number of columns in the table")
    
    # ������ ��������� ��������� ������
    args = parser.parse_args()

    # ����� ������� ��� ��������� HTML-����� � �������� ����������� ����� � ��������
    generate_html_table(args.rows, args.cols)

if __name__ == "__main__":
    main()
