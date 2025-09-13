# Program: Task 4
# Lab Number: 3
# Program Version: 1.1
# Developer: Lishyk Ksenia
# Date: 27.03.2024
from text_processing import count_uppercase_letters, find_first_word_with_z, exclude_words_starting_with_a
from time_decorator import measure_time

@measure_time
def main():
    """
    Main function to execute the program
    """
    while True:
        text = "So  she wasz considering zin her own mind, as well as she could, for the hot day made her feel very sleepy and stupid, whether the pleasure of making a daisy-chain would be worth the trouble of getting up and picking the daisies, when suddenly a White Rabbit with pink eyes ran close by her."
        print("\n", text, "\n")

        # a) Count uppercase letters
        uppercase_count = count_uppercase_letters(text)
        print(f"Number of uppercase letters: {uppercase_count}")

        # b) Find first word containing 'z' and its position
        first_word_with_z, position = find_first_word_with_z(text)
        if first_word_with_z:
            print(f"First word containing 'z': '{first_word_with_z}', Position: {position}")
        else:
            print("No word containing 'z' found.")

        # c) Exclude words starting with 'a'
        text_excluded_a = exclude_words_starting_with_a(text)

        print(f"Text excluding words starting with 'a':\n{text_excluded_a}")
    
        choice = input("Do you want to check another string (Y/N)? ").upper()
        if choice != 'Y':
                break
        if choice == 'N':
                break
    
if __name__ == "__main__":
    main()
