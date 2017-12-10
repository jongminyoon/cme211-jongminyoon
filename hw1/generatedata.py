import sys, random

if __name__ == "__main__":
    if len(sys.argv) <= 5:
        # no arguments, print usage message
        print("Usage:")
        print("  $ python3 generatedata.py <ref_length> <nreads> <read_len> <ref_file> <reads_file>")
        sys.exit(0)

    ref_length = int(sys.argv[1])
    nreads     = int(sys.argv[2])
    read_len   = int(sys.argv[3])
    ref_file   = sys.argv[4]
    reads_file = sys.argv[5]

    print("reference length: " + str(ref_length))
    print("number reads: " + str(nreads))
    print("read length: " + str(read_len))

    len75 = int(0.75*ref_length)

    if read_len > len75:
        print("read length too long to have reads which align twice.")
        sys.exit(0)

    ref = ""
    reads = []

    def generate(l):
        ref = ""
        for i in range(0,l):
            temp = random.randint(0,3)
            if temp == 0:
                ref += "A"
            elif temp == 1:
                ref += "G"
            elif temp == 2:
                ref += "C"
            else:
                ref += "T"
        return ref


    # generate first 75% of the reference
    ref = generate(len75)

    # copy the last 25%
    ref += ref[-(ref_length-len75):]

    # write the reference to the file
    with open(ref_file,'w') as f:
        f.write(ref)

    a0 = 0
    a1 = 0
    a2 = 0

    # generate reads
    for i in range(nreads):
        temp = random.random()
        if temp < 0.75:
            a1 += 1
            ind = random.randint(0,2*len75-ref_length -1)
            reads.append(ref[ind:ind+read_len])
        elif temp < 0.85:
            a2 += 1
            ind = random.randint(len75+read_len, ref_length)
            reads.append(ref[ind - read_len:ind])
        else:
            a0 += 1
            while True:
                temp_read = generate(read_len)
                if ref.find(temp_read) == -1:
                    break
            reads.append(temp_read)

    if nreads != a0+a1+a2:
        print("sth wrong")

    print("aligns 0: " + str(a0/nreads))
    print("aligns 1: " + str(a1/nreads))
    print("aligns 2: " + str(a2/nreads))

    # write the reads to the file
    with open(reads_file,'w') as f:
        for s in reads:
            f.write(s + "\n")











