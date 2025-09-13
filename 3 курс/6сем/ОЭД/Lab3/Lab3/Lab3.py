#coding: windows-1251
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as stats

def load_data(filepath):
    return pd.read_csv(filepath)

def sample_data(df, n=200, seed=42):
    return df.sample(n=n, random_state=seed)

def calculate_correlation_matrix(df):
    corr = df.corr(numeric_only=True)
    plt.figure(figsize=(8, 6))
    sns.heatmap(corr, annot=True, cmap='coolwarm', fmt=".3f")
    plt.title('Корреляционная матрица')
    plt.show()
    return corr

def filter_by_correlation(df, y_col='Production', threshold=0.4):
    numeric_df = df.select_dtypes(include='number')
    # by default - pirson
    corr_matrix = numeric_df.corr() 
    
    target_corr = corr_matrix[y_col].drop(y_col)  # исключаем саму y
    selected_features = target_corr[abs(target_corr) >= threshold].index.tolist()
    
    print(f"Сохраняем только признаки с |r| >= {threshold} по отношению к '{y_col}': {selected_features}")
    
    return df[[y_col] + selected_features]


def show_top_corr_pairplot(df, y_col='Production', top_n=4):
    numeric_df = df.select_dtypes(include='number')
    corr = numeric_df.corr()[y_col].drop(y_col).abs().sort_values(ascending=False)
    top_features = corr.head(top_n).index.tolist()
    
    print(f"\nТоп-{top_n} признаков по корреляции с '{y_col}': {top_features}")
    selected = df[[y_col] + top_features]
    
    sns.pairplot(selected)
    plt.suptitle(f'Pairplot: {y_col} и топ-{top_n} признаков', y=1.02)
    plt.show()


def plot_correlation_lines(df, y_col='Production', top_n=4):
    
    numeric_df = df.select_dtypes(include='number')
    corr = numeric_df.corr()[y_col].drop(y_col).abs().sort_values(ascending=False)
    top_features = corr.head(top_n).index.tolist()
    
    print(f"\nПостроение линий корреляции для топ-{top_n} признаков по '{y_col}'")

    for feature in top_features:
        plt.figure(figsize=(6, 4))
        sns.regplot(x=feature, y=y_col, data=df, line_kws={"color": "red"})
        plt.title(f"Корреляция между '{feature}' и '{y_col}'")
        
        # Добавим значение корреляции
        r, _ = stats.pearsonr(df[feature], df[y_col])
        plt.xlabel(f"{feature} (r = {r:.3f})")
        plt.ylabel(y_col)
        
        plt.tight_layout()
        plt.show()

df = load_data('crop_yield_output.csv')

# if df['Annual_Rainfall'].dtype == 'object':
#     df['Annual_Rainfall'] = df['Annual_Rainfall'].map({'No': 0, 'Yes': 1})

sampled_df = sample_data(df, 100)

print("Корреляционная матрица (до отбора):")
original_corr = calculate_correlation_matrix(sampled_df)

filtered_df = filter_by_correlation(sampled_df, y_col='Production')

print("Корреляционная матрица (после отбора):")
calculate_correlation_matrix(filtered_df)

show_top_corr_pairplot(sampled_df, y_col='Production', top_n=4)

plot_correlation_lines(sampled_df, y_col='Production', top_n=4)
