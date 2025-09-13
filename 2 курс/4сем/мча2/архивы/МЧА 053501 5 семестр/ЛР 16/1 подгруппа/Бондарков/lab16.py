from statistics import median


def clean(string, symb):
    string.lower()
    symbarr = list(symb)

    for i in symbarr:
        string = string.replace(i, ' ')
    return string


def repetition(string):
    string = clean(string, "!.,?")
    string = string.split()
    d = {i: 1 for i in string}
    repetitions = []

    for i in string:
        if i not in repetitions:
            repetitions.append(i)
            for j in string:
                if i == j:
                    d[i] += 1
    return d


def topk_ngram(string):
    k = int(input("Enter top-K: "))
    n = int(input("Enter N-gram: "))
    string = clean(string, "?!.,")
    string = string.split()

    for i in string:
        if len(i) < n:
            string[string.index(i)] = ""
    string = " ".join(string)
    string = string.split()

    for i in string:
        string[string.index(i)] = i[:n]
    d = {i: 1 for i in string}
    repetitions = []

    for i in string:
        if i not in repetitions:
            repetitions.append(i)
            for j in string:
                if i == j:
                    d[i] += 1
    list_d = list(d.items())
    list_d.sort(key=lambda l: l[1])
    list_d.reverse()
    print(*enumerate(list_d[:k]), sep='\n')


def average(string):
    string = clean(string, "!,?")
    string = string.split(".")
    count_of_sentences = len(string)
    string = "".join(string)
    string = clean(string, ".")
    string = string.split()
    count_of_words = len(string)
    return count_of_words/count_of_sentences


def medi(string):
    string = clean(string, "!,?")
    m = median([len(sentence.split()) for sentence in string.split(".")])
    return m