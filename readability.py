from cs50 import get_string

# calculate letters


def count_letters(text):
    count_letters = 0

    for i in text:
        tmp = ord(i)
        if tmp > 64 and tmp < 91:
            count_letters += 1
        elif tmp > 96 and tmp < 123:
            count_letters += 1

    return count_letters

# calculate words


def count_words(text):
    count_words = 1

    for i in text:
        if i == " ":
            count_words += 1

    return count_words

# calculate sentences


def count_sentences(text):
    count_sentences = 0
    for i in text:
        if i == '.':
            count_sentences += 1
        if i == '!':
            count_sentences += 1
        if i == '?':
            count_sentences = + 1

    return count_sentences


# get text
text = get_string("Text: ")

letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

# calculate Grade
letters_percent = (letters * 100) / words
sentences_percent = (sentences * 100) / words
answer = 0.0588 * letters_percent - 0.296 * sentences_percent - 15.8
final_answer = round(answer)

if (final_answer < 1):
    print("Before Grade 1")
elif(final_answer >= 1 and final_answer < 16):
    print(f"Grade {final_answer}")
else:
    print("Grade 16+")
