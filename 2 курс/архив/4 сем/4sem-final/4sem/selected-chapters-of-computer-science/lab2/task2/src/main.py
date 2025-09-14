from app import App


def main():
    try:
        App().start_application()
    except KeyboardInterrupt:
        print('\nThank you for using our application! Bye!')


if __name__ == "__main__":
    main()
