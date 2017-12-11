import sys, time, math

if __name__ == "__main__":
    if len(sys.argv) <= 2:
        # no arguments, print usage message
        print("Usage:")
        print("  $ python3 similarity.py <data_file> <output_file> [user_thresh (default = 5)]")
        sys.exit(0)

    data_file   = sys.argv[1]
    output_file = sys.argv[2]
    if len(sys.argv) == 4:
        user_thresh = int(sys.argv[3])
    else:
        user_thresh = 5

    print("Input MovieLens file: " + data_file)
    print("Output file for similarity data: " + output_file)
    print("Minimum number of common users: " + str(user_thresh))

    # create a dictionary of dictionary saving the movie rating data. movie:{user:rating} structure.
    data = dict()
    n_line = 0
    n_user = 0
    n_movie = 0
    user_set = set()
    with open(data_file,'r') as f:
        for line in f:
            if line == "":
                continue
            n_line += 1
            user, movie, rating, temp = (int(x) for x in line.split())
            
            if user not in user_set:
                user_set.add(user)
                n_user += 1

            if movie in data.keys():
                data[movie][user] = rating
            else:
                data[movie] = {user:rating}
                n_movie += 1

    print("Read {} lines with total of {} movies and {} users".format(n_line,n_movie,n_user))

    def r_ave(movie, data):
        if movie in data.keys():
            return sum(data[movie].values())/len(data[movie])
        else:
            return 0

    def similarity(a,b,data, user_thresh):
        common_users = set(data[a].keys())&set(data[b].keys())
        if len(common_users) < user_thresh:
            return -2
        a_ave = r_ave(a,data)
        b_ave = r_ave(b,data)

        denom_a = math.sqrt(sum((data[a][user]-a_ave)**2 for user in common_users))
        denom_b = math.sqrt(sum((data[b][user]-b_ave)**2 for user in common_users))

        if math.isclose(denom_a, 0.) & math.isclose(denom_b, 0.):
            return 1.
        elif math.isclose(denom_a, 0.):
            return sum(data[b][user]-b_ave for user in common_users) / denom_b
        elif math.isclose(denom_b, 0.):
            return sum(data[a][user]-a_ave for user in common_users) / denom_a
        else:
            nom = sum((data[b][user]-b_ave)*(data[a][user]-a_ave) for user in common_users)
            return nom/denom_a/denom_b


    def most_similar(movie,data, user_thresh):
        b = list(data.keys())
        b.remove(movie)
        p = [similarity(movie,x,data,user_thresh) for x in b]
        r_max = max(p)
        ind_max = p.index(r_max)

        if r_max < -1.5:
            return ()  # empty tuple
        else:
            b_max = b[ind_max]
            common_users = set(data[movie].keys())&set(data[b_max].keys())
            return b_max, r_max, len(common_users)



    t0 = time.time()

    a = list(data.keys())
    b = [(x,most_similar(x,data,user_thresh)) for x in a]
    final = sorted(b, key = lambda x:x[0])

    t1 = time.time()

    print("Computed similarities in {} seconds".format(t1-t0))

    with open(output_file,'w') as f:
        for a,b in final:
            f.write(str(a))
            if len(b) == 3:
                f.write(" "+str(b))
            f.write("\n")
