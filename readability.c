#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //get Text
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //calculate Grade
    float letters_percent = (letters * 100) / words, sentences_percent = (sentences * 100) / words;
    float answer = 0.0588 * letters_percent - 0.296 * sentences_percent - 15.8;
    int final_answer = round(answer);

    if (final_answer < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final_answer >= 1 && final_answer < 16)
    {
        printf("Grade %i\n", final_answer);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

//calculate letters
int count_letters(string text)
{
    int count_letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count_letters ++;
        }
    }
    return count_letters;
}

//calculate words
int count_words(string text)
{
    int count_words = 0;
    string cuma = "'";
    char g = ' ';
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count_words ++;
        }
        if (text[i] == cuma[0])
        {
            count_words ++;
        }
        if (g + text[i] == cuma[0] + 's')
        {
            count_words --;
        }
        g = text[i];
    }
    return count_words + 1;
}

//calculate sentences
int count_sentences(string text)
{
    int count_sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.')
        {
            count_sentences ++;
        }
        if (text[i] == '!')
        {
            count_sentences ++;
        }
        if (text[i] == '?')
        {
            count_sentences ++;
        }
    }
    return count_sentences;
}
