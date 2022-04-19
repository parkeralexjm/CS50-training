from cs50 import get_string


def main():
    # Get the text from the user
    text = get_string("Text: ")
    # Count the number of letters in the text given by the user then set that value to letters
    letters = len(text) - text.count(" ") - text.count(",") - text.count(".") - text.count("!") - text.count("?") - text.count("'")
    words = (text.count(" ") + 1)
    sentences = text.count(".") + text.count("!") + text.count("?")
    # Calculate the average words
    avg_words = 100.0 / words
    # Calculate the average letters per 100 words
    L = avg_words * letters * 0.0588
    # Calculate the average sentences per 100 words
    S = avg_words * sentences * 0.296
    # Calculate the Coleman_Liau index
    index = round(L - S - 15.8)
    # Compare the index against the grade
    if index < 1:
        print("Before Grade 1")
        exit()
    elif index > 15:
        print("Grade 16+")
        exit()
    else:
        print(f"Grade {index}")
        exit()


main()