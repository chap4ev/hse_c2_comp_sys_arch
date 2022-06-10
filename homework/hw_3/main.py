import sys
from pathlib import Path

from src.container import Container
from src.exceptions import ParseError

if __name__ == '__main__':
    args = sys.argv
    if len(args) != 5 or args[1] not in ["-n", "-f"]:
        print("incorrect command line!\n"
              "  Waited:\n"
              "     command -f infile outfile01 outfile02\n"
              "  Or:\n"
              "     command -n number outfile01 outfile02")
        exit()

    count = None
    input_file = None
    out_file1 = None
    out_file2 = None
    container = Container()

    if args[1] == "-n":
        count = args[2]
        out_file1 = args[3]
        out_file2 = args[4]
        if not count.isdigit():
            print(f"err random fill: invalid number of elements {count}")
            exit()
        count = int(count)
        if not 1 < count <= 10000:
            print(f"err random fill: invalid number of elements {count}"
                  "Set 0 < number <= 10000")
            exit()
        container.fill_randomly(count)
    elif args[1] == "-f":
        input_file = args[2]
        out_file1 = args[3]
        out_file2 = args[4]
        if not Path(input_file).is_file():
            print(f"err input file fill: input file \"{input_file}\" does not exist")
            exit()
        try:
            container.fill_from_file(input_file)
        except ParseError as e:
            print(f"err filling container: {repr(e)}")
            exit()

    with open(out_file1, 'w') as out:
        out.write("Filled Container:\n")
        for i, language in enumerate(container):
            out.write(f"{i}: {language}\n")

    container.sort()

    with open(out_file2, 'w') as out:
        out.write("Sorted Container:\n")
        for i, language in enumerate(container):
            out.write(f"{i}: {language}\n")
