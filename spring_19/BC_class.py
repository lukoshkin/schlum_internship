import numpy as np
from math import log2
from math import floor,ceil

class BC:
    def __init__(self, X):
        self.set = X
        self.sma = X.min(0)
        self.len = X.max(0) - self.sma
        self.L_max  = self.len.max()
        self.xamax  = X.argmax(0)
        self.n_cols = X.shape[1]
        
    def FD_curve(self, n_pts=40, eps=.5):
        satur = log2(2 * eps / self.L_max)
        Ds = np.logspace(satur, 1, n_pts, base=2) / eps
        
        bin_map = np.floor((self.set - self.sma) * Ds[:, None, None])
        
        tmp = self.len * Ds[:, None]
        bin_map[:, self.xamax, np.arange(self.n_cols)] = np.ceil(tmp)
        
        np.ceil(tmp, out=tmp)
        ones = np.ones(len(Ds))[:, None]
        mult = np.hstack((ones, tmp.cumprod(1)[:, :-1]))
        
        which_box = np.einsum('ijk,ik->ij', bin_map, mult).astype(int)
  
        def counter(row):
            _, c = np.unique(row, return_counts=True)
            return np.einsum('i,i', c, c)
        
        S = np.apply_along_axis(counter, 1, which_box)
        
        return -np.log2(Ds), np.log2(S)