import glob, os, math

class Airfoil:
    """ Airfoil Class
    
    Attributes
    
    count : number of coordinates.
    xy[0] : x coordinates, xy[1] : y coordinates, both are lists
    alphas : dictionary {alpha : [list of the pressure coefficients]}
    chordlength = chord length, from tail to head.
    cl : dictionary, {alpha : cl}
    stgpt : dictionary, {alpha : [(x,y),cp]} """
    
    def __init__(self,inputdir):
        self.read_data(inputdir)
        self.find_chordlength()
        self.find_cl()
        self.find_stgpt()

    def read_data(self,inputdir):
        files = glob.glob(inputdir+"*")
        if len(files) == 1:
            raise RuntimeError(inputdir + " is not a valid directory.")
        filenames = [os.path.split(x)[1] for x in files]
        if 'xy.dat' not in filenames:
            raise RuntimeError("x,y coordiante file is not in the directory.")

        # read xy.dat
        self.count = 0
        try:
            with open(inputdir+'xy.dat','r') as f:
                case_name = f.readline()
                self.xy = [[],[]]
                for line in f:
                    if line =='': # if the end of the file has empty lines
                        continue
                    self.xy[0].append(float(line.split()[0]))
                    self.xy[1].append(float(line.split()[1]))
                    self.count += 1
        except Exception as e:
            raise RuntimeError("Wrong data format in xy.dat")

        
        filenames.remove('xy.dat')
        if len(filenames) == 0:
            raise RuntimeError("There is no pressure coefficient data file.")
        
        if not all(len(x) > 9 and x[0:5] == 'alpha' and x[-4:] =='.dat' for x in filenames):
            raise RuntimeError("There is a pressure coefficient file with a wrong name.")


        # read alphas and pressrue coefficients
        self.alphas = dict()
        for x in filenames:
            cpcount = 0
            temp = x[5:-4]
            try:
                self.alphas[float(temp)] = []
                with open(inputdir + x, 'r') as f:
                    f.readline()
                    for line in f:
                        if line =='': # if the end of the file has empty lines
                            continue
                        self.alphas[float(temp)].append(float(line))
                        cpcount += 1
            except Exception as e:
                raise RuntimeError("There is a pressure coefficient file with a wrong name.")
            if cpcount != self.count-1:
                raise RuntimeError("The number of pressure coefficients in alpha = {} is not consistent with the number of (x,y) coordinates".format(float(temp)))

            
    def find_chordlength(self):
        x_max = max(self.xy[0])
        y_max = self.xy[1][self.xy[0].index(x_max)]
        x_min = min(self.xy[0])
        y_min = self.xy[1][self.xy[0].index(x_min)]
        self.chordlength = math.sqrt((x_max-x_min)**2 + (y_max-y_min)**2)

    def find_cl(self):
        deltax = [self.xy[0][i+1]-self.xy[0][i] for i in range(self.count-1)]
        deltay = [self.xy[1][i+1]-self.xy[1][i] for i in range(self.count-1)]

        self.cl = dict()
        for alpha in self.alphas.keys():
            cy = sum(a*b for (a,b) in zip(self.alphas[alpha],deltax))
            cx = -sum(a*b for (a,b) in zip(self.alphas[alpha],deltay))
            self.cl[alpha] = (math.cos(alpha)*cy - math.sin(alpha)*cx)/self.chordlength

    def find_stgpt(self):
        self.stgpt = dict()
        for alpha in self.alphas.keys():
            cp = max(x for x in self.alphas[alpha])
            ind = self.alphas[alpha].index(cp)
            coord = ((self.xy[0][ind]+self.xy[0][ind+1])/2,(self.xy[1][ind]+self.xy[1][ind+1])/2)
            self.stgpt[alpha] = [coord,cp]

    def __repr__(self):
        string  = "alpha      cl            stagnation pt\n"
        string += "-----   -------   ----------------------------\n"
        for alpha in sorted(self.alphas.keys()):
            string += "{: 4.2f}  {: 8.4f}    ({: 4.4f}, {: 4.4f}) {: 4.4f}\n".format(alpha, self.cl[alpha], self.stgpt[alpha][0][0], self.stgpt[alpha][0][1], self.stgpt[alpha][1])
        return string