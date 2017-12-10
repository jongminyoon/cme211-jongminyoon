import sys, time

if __name__ == "__main__":
    if len(sys.argv) <= 3:
        # no arguments, print usage message
        print("Usage:")
        print("  $ python3 processdata.py <ref_file> <reads_file> <align_file>")
        sys.exit(0)

    ref_file   = sys.argv[1]
    reads_file = sys.argv[2]
    align_file = sys.argv[3]

    with open(ref_file,'r') as f:
        ref = f.read()

    ref_length = len(ref)

    if ref_length == 0:
        print("Empty reference file")
        sys.exit(0)


    with open(reads_file,'r') as f:
        reads = f.readlines()

    reads = [x.strip() for x in reads]
    if reads[-1] == "":
        reads.pop()
    nreads = len(reads)

    if nreads == 0:
        print("Empty reads file")
        sys.exit(0)

    read_len = len(reads[0])


    print("reference length: " + str(ref_length))
    print("number reads: " + str(nreads))

    a0 = 0
    a1 = 0
    a2 = 0

    align = []

    t0 = time.time()
    for i in range(nreads):
        read = reads[i]
        ind = 0
        inds = []
        while True:
            ind = ref.find(read,ind)
            if ind == -1:
                break
            else:
                inds.append(ind)
            ind += 1
        
        count = len(inds)

        if count == 0:
            a0 += 1
            inds.append(-1)
        elif count == 1:
            a1 += 1
        else:
            a2 += 1

        align.append(inds)

    t1 = time.time()

    if nreads != a0+a1+a2:
        print("sth wrong")

    print("aligns 0: " + str(a0/nreads))
    print("aligns 1: " + str(a1/nreads))
    print("aligns 2: " + str(a2/nreads))
    print("elapsed time: " + str(t1-t0))

    # write the reads to the file
    with open(align_file,'w') as f:
        for i in range(nreads):
            f.write(reads[i])
            for j in align[i]:
                f.write(" " + str(j))
            f.write("\n")
