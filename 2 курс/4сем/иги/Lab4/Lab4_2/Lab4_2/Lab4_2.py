from file_reader import FileReader
from text_analyzer import TextAnalyzer
from text_statistics import TextStatistics
from file_archiver import FileArchiver

def main():
    while True: 
        # Чтение текста из файла
        reader = FileReader('input.txt')
        text = reader.read_text()
        
        # Создание файла output.txt для записи результатов
        with open('output.txt', 'w') as output_file:
            if text:
                analyzer = TextAnalyzer(text)
                sentences = analyzer.find_sentences()
                smileys = analyzer.find_smileys()
                binary_numbers = analyzer.find_binary_numbers()
                vowel_consonant_words = analyzer.find_vowel_consonant_words()
                words_after_comma = analyzer.find_words_after_comma()
                words_start_end_vowels = analyzer.find_words_start_end_vowels()

                statistics = TextStatistics(text)
                sentence_count = statistics.count_sentences()
                narr_count, interrog_count, imper_count = statistics.count_sentence_types()
                avg_sentence_length = statistics.average_sentence_length()
                avg_word_length = statistics.average_word_length()
                smiley_count = statistics.count_smileys()
                start_vowel_count, end_vowel_count = statistics.count_words_start_end_vowels()
                char_counts = statistics.count_character_occurrences()
                
                # Вывод результатов на консоль
                print("Total sentences:", sentence_count)
                print("Sentences:", sentences)
                print("Narrative sentences:", narr_count)
                print("Interrogative sentences:", interrog_count)
                print("Imperative sentences:", imper_count)
                print("Average sentence length:", avg_sentence_length)
                print("Average word length:", avg_word_length)
                print("Smiley count:", smiley_count, smileys)
                print("Binary numbers:", binary_numbers)
                print("Vowel-consonant words:", vowel_consonant_words)
                print("Start vowel words count:", start_vowel_count)
                print("End vowel words count:", end_vowel_count)
                print("List of start-end vowels:", words_start_end_vowels)
                print("Character occurrences:")
                for char, count in char_counts.items():
                    print(f"{char}: {count}")
                print("Words after comma (sorted):", words_after_comma)
                
                # Запись результатов в файл output.txt
                output_file.write("Total sentences: {}\n".format(sentence_count))
                output_file.write("Sentences: {}\n".format(sentences))
                output_file.write("Narrative sentences: {}\n".format(narr_count))
                output_file.write("Interrogative sentences: {}\n".format(interrog_count))
                output_file.write("Imperative sentences: {}\n".format(imper_count))
                output_file.write("Average sentence length: {}\n".format(avg_sentence_length))
                output_file.write("Average word length: {}\n".format(avg_word_length))
                output_file.write("Smiley count: {} {}\n".format(smiley_count, smileys))
                output_file.write("Binary numbers: {}\n".format(binary_numbers))
                output_file.write("Vowel-consonant words: {}\n".format(vowel_consonant_words))
                output_file.write("Start vowel words count: {}\n".format(start_vowel_count))
                output_file.write("End vowel words count: {}\n".format(end_vowel_count))
                output_file.write("List of start-end vowels: {}\n".format(words_start_end_vowels))
                output_file.write("Character occurrences:\n")
                for char, count in char_counts.items():
                    output_file.write("{}: {}\n".format(char, count))
                output_file.write("Words after comma (sorted): {}\n".format(words_after_comma))
                output_file.close()
                # Архивирование результатов
                FileArchiver.create_archive('output.txt', 'result.zip')

        repeat = input("Do you want to run the program again? (y/n): ")
        if repeat.lower() != 'y':
            break

if __name__ == "__main__":
    main()

