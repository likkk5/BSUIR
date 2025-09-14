from helpers import (
    calculate_average_length_of_words,
    calculate_amount_of_sentences,
    calculate_amount_of_non_declarative_sentences,
    calculate_average_length_of_sentences,
    get_k_repeated_ngrams,
)


def main():
    text = input('Enter your text: ')

    print('Average length of the sentence in characters (words count only): ',
          calculate_average_length_of_sentences(text))

    print('Average length of the word in the text in characters: ',
          calculate_average_length_of_words(text))

    print('Amount of sentences in the text: ',
          calculate_amount_of_sentences(text))

    print('Amount of non-declarative sentences in the text: ',
          calculate_amount_of_non_declarative_sentences(text))

    try:
        k, n = map(int, input('Enter K and N to get top-K repeated N-grams in the text: ').split())
        print('Top-K repeated N-grams in the text:')

        k_repeated = get_k_repeated_ngrams(text, k, n)
        for ngram, count in k_repeated:
            print(f'Ngram "{" ".join(ngram)}" appears {count} time{"s" if count > 1 else ""}')
    except ValueError:
        print('Invalid input')
        exit(1)


if __name__ == '__main__':
    main()
