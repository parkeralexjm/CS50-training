

def main():
    height = get_height()
    for i in range(height):
        print(" " * (height - (i + 1)), end="")
        print("#" * (i + 1))


def get_height():
    while True:
        try:
            answer = int(input("Height: "))
            if answer < 9 and answer > 0:
                break
        except ValueError:
            print("Incorrect value")
    return answer

    
main()