from cs50 import get_string


def count_letters(context):  # counting letters function
    l = 0
    for i in context:
        if i.isalpha():
            l += 1
    return l


def count_words(context):  # counting words function
    w = 1
    for i in context:
        if i.isspace():
            w += 1
    return w


def count_sentences(context):  # counting sentences function
    s = 0
    for i in context:
        if i in ".!?":
            s += 1
    return s


def index_grade(letters, sentences, words):                # Coleman-Liau index grading formula
    L = float(letters / words * 100)
    S = float(sentences/words * 100)
    index = int(round(0.0588 * L - 0.296 * S - 15.8))
    return index


context = get_string(" Enter the paragraph =")  # getting the context

letters = count_letters(context)
words = count_words(context)
sentences = count_sentences(context)

grade = index_grade(letters, sentences, words)

if grade < 1:  # conditions basis on grades
    print("Before Grade 1")

elif grade == 1:
    print("Grade 1")

elif grade == 2:
    print("Grade 2")

elif grade == 3:
    print("Before Grade 3")

elif grade == 4:
    print("Before Grade 4")

elif grade == 5:
    print("Before Grade 5")

elif grade == 6:
    print("Before Grade 6")

elif grade == 7:
    print("Before Grade 7")

elif grade == 8:
    print("Before Grade 8")

elif grade == 9:
    print("Before Grade 9")

elif grade == 10:
    print("Before Grade 10")

else:
    print("Grade 16+")
