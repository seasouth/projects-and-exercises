
class Number:
    def __init__(self, v):
        "CODE HERE to intialize the object"
        self.v = v;
    def toString(self):
        "CODE HERE to print the number in mulitple formats: decimal, hex, binary"
        #h = format(self.v, '016x')
        h = hex(self.v)
        b = bin(self.v)
        d = int(self.v)

        s = str(d) + "    " + str(h) + "    " + str(b)
        return s



while True:
    print("When entering numbers, you can enter:")
    print("     A normal decimal integer number as big as 2^{64}-1.")
    print("     An integer number in hex up to 16 digits, starting with 0x.")
    print("     An integer number in binary up to 64 digits, starting with 0b.")
    print("Enter a problem: number AND|OR|XOR|LS|RS|ANDNOT number:")

    try:
        inputStr = input()
    except (EOFError):
        exit()

    """
    CODE HERE to interpret inputs/operators, and perform operations.

    """
    if inputStr == None or inputStr == "exit" or inputStr == "":
        exit()
    ops = inputStr.split()
    if len(ops) != 3:
        print("Invalid input")
        exit()
    if ops[0] == None:
        print("Bad format for the first number")
        exit()
    if ops[0][0] == "B":
        ops[0] = ops[0][1:]
        ops[0] = int(ops[0], 2)
    elif ops[0][0:2] == "0x":
        ops[0] = ops[0][2:]
        ops[0] = int(ops[0], 16)
    try:
        if ops[2][0] == "B":
            ops[2] = ops[2][1:]
            ops[2] = int(ops[2], 2)
        elif ops[2][0:2] == "0x":
            ops[2] = ops[2][2:]
            ops[2] = int(ops[2], 16)
    except(IndexError):
        print("Invalid input")
        exit()
    try:    
        a = int(ops[0])
    except(ValueError):
        print("Invalid first number")
        exit();
    try:
        b = int(ops[2])
    except(ValueError):
        print("Invalid second number")
        exit();
    except(IndexError):
        print("Invalid input")
    numberA = Number(a)
    numberB = Number(b)
    operation = ops[1]
    numberC = None
    if operation == "AND":
        numberC = Number(numberA.v & numberB.v)
    elif operation == "OR":
        numberC = Number(numberA.v | numberB.v)
    elif operation == "XOR":
        numberC = Number(numberA.v ^ numberB.v)
    elif operation == "LS":
        numberC = Number(numberA.v << numberB.v)
    elif operation == "RS":
        numberC = Number(numberA.v >> numberB.v)
    elif operation == "ANDNOT":
        numberC = Number(numberA.v & ~numberB.v)
    else:
        print("Bad operator")
        exit()

    """
    Outputs, dont change the following because we're grading based on this.
    We're going to grade by testing it with a .txt file with some sample inputs,
    and we expect to see results like:

    Operation: AND
    A: 5    0x5    0b101
    B: 9    0x9    0b1001
    C: 1    0x1    0b1

      (this example takes input:   5 AND 9  )


    Make sure your code reads the input correctly
    """
    # output
    print("\nCompute Result:")
    print("     Operation: ", operation)
    print("     A: ", numberA.toString())
    print("     B: ", numberB.toString())
    print("     C: ", numberC.toString())
