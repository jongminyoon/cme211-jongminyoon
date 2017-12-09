import sys

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        # no arguments, print usage message
        print("Usage:")
        print("  $ python3 echo_commands.py [arguments]")
        sys.exit(0)
    # echo arguments
    for i in range(len(sys.argv)):
        print(i,sys.argv[i])
