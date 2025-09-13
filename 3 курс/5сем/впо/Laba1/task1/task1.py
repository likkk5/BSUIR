import random

def generate_exclamation_string():
    exclamation_count = random.randint(5, 50)
    return "!" * exclamation_count

def main():
    print("Hello, World!")
    print("Andhiagain!")
    print(generate_exclamation_string())

if __name__ == "__main__":
    main()

