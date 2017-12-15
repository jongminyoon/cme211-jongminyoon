import numpy as np
import matplotlib.pyplot as plt
from scipy.sparse import csr_matrix
from scipy.sparse.linalg import spsolve
import warnings
import math





class Truss:

    def __init__(self,input):
        self.joints_file = input[0]
        self.beams_file = input[1]

        # read files
        self.joints = np.loadtxt(self.joints_file, dtype=np.float64)[:,1:]
        self.beams = np.loadtxt(self.beams_file, dtype=np.int8)[:,1:]

        if len(input) >= 3:
            self.PlotGeometry(input[2])

        self.n_joints = self.joints.shape[0]
        self.n_beams = self.beams.shape[0]

        self.mat()
        if self.Amat.shape[0] < self.n_beams:
            raise RuntimeError("Truss geometry not suitable for static equilibrium analysis : overdetermined")
        self.F = -np.concatenate((self.joints[self.joints[:,4]==0,2],self.joints[self.joints[:,4]==0,3]), axis=0)

        warnings.filterwarnings('error')
        try:
            self.B = spsolve(self.Amat, self.F)
        except Exception as e:
            raise RuntimeError("Cannot solve the linear system, unstable truss?")

    def mat(self):
        """ create matrix with zerodisp joints removed, and with n_beams columns."""
        nx = self.n_joints - sum(self.joints[:,4])
        ny = self.n_beams
        row = []
        col = []
        data = []
        for i, [a,b] in enumerate(self.beams):
            yb = self.joints[b-1,1]
            ya = self.joints[a-1,1]
            xb = self.joints[b-1,0]
            xa = self.joints[a-1,0]

            hyp = math.sqrt((yb-ya)**2 + (xb-xa)**2)
            c = (xb-xa)/hyp
            s = (yb-ya)/hyp

            if self.joints[b-1,4] == 0:
                bprime = b - sum(self.joints[0:b,4]) # new index after removing the zerodisp joints
                # Bx at Jb
                row.append(bprime-1)
                col.append(i)
                data.append(c)
                # By at Jb
                row.append(bprime-1+nx)
                col.append(i)
                data.append(s)
            if self.joints[a-1,4] == 0:
                aprime = a - sum(self.joints[0:a,4])
                # Bx at Ja
                row.append(aprime-1)
                col.append(i)
                data.append(-c)
                # By at Ja
                row.append(aprime-1+nx)
                col.append(i)
                data.append(-s)
        self.Amat = csr_matrix((data,(row,col)), shape = (2*nx,self.n_beams))


    def PlotGeometry(self,output):
        for a,b in self.beams:
            yb = self.joints[b-1,1]
            ya = self.joints[a-1,1]
            xb = self.joints[b-1,0]
            xa = self.joints[a-1,0]
            plt.plot([xa,xb],[ya,yb], 'b')

        plt.savefig(output)

    def __repr__(self):
        string  = "Beam    Force\n"
        string += "----   -------\n"
        for i, bf in enumerate(self.B):
            string += "  " + str(i) + "  {: 8.3f}\n".format(bf)
        return string
