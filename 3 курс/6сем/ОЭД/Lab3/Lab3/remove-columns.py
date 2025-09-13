import pandas as pd

def load_and_clean_data(filepath, output_path):
    # Загружаем CSV
    df = pd.read_csv(filepath)

    # Удаляем ненужные столбцы
    columns_to_drop = ['Crop', 'Crop_Year', 'Season', 'State', 'Yield']
    df_cleaned = df.drop(columns=columns_to_drop)

    # Сохраняем обновлённый DataFrame в новый CSV
    df_cleaned.to_csv(output_path, index=False)

    return df_cleaned

# Пути к файлам
input_file = 'crop_yield.csv'
output_file = 'crop_yield_output.csv'

# Обработка
df = load_and_clean_data(input_file, output_file)

# Проверка
print(df.head())
