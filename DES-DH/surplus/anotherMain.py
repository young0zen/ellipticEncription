import dh

def generateP():
    print("Please input p:")
    p = (int)(input())
    return p

def generatePub(p):
    gen = dh.get_generator_of(p)

    if (gen == -1):
        print("Invalid Input. Aborting...")
        quit()

    print("Please give a Pri:")
    pri = int(input())
    pub = dh.compute_public_val(gen, pri, p)
    return pub

if __name__ == '__main__':
    p = generateP()
    pubA = generatePub(p)
    pubB = generatePub(p)
