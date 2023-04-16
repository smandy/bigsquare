from pprint import pprint as pp
import copy    

def partition(xs,n):
    ret = []
    while xs:
        xs, chunk = xs[n:], xs[:n]
        ret.append(chunk)
    return ret

class Grid:
    def __init__(self, n, datum = ' '):
        # TODO - data can be a numpy 'repeat' here maybe
        self.data = [datum] * ( n * n)
        self.n = n
    def idx(self, x):
        return x[0]*self.n + x[1]
    def __getitem__(self, x):
        return self.data[ self.idx(x)  ]
    def __setitem__(self, x, n):
        #print("Setitem %s %s" % (x,n))
        self.data[ self.idx(x) ] = n

    def __repr__(self):
        return "\n".join( [ "".join( [str(y) for y in x ] ) for x in partition(self.data, self.n)  ] )

    def biggest(self):
        xextents = Grid(self.n, 0)
        yextents = Grid(self.n, 0)

        # Calculate largest candidate squares (n^2) :-(
        # Step 1 - how far do 1's extend along x+y at each point
        for y in range(self.n):
            count = 0
            for x in range(self.n):
                if self[y,x]==' ':
                    count = 0
                else:
                    count += 1
                xextents[y,x] = count
                
        for x in range(self.n):
            count = 0
            for y in range(self.n):
                if self[y,x]==' ':
                    count = 0
                else:
                    count += 1
                yextents[y,x] = count

                
        # Step 2 - size of potential square at each point is min of x + y extension
        # Collect a list of the potential squares of each size from smallest to biggest
        bests = [None] * (self.n+1) # Fencepost! To allow indexing self.n
        for i in range(self.n):
            for j in range(self.n):
                sz = min([yextents[i,j], xextents[i,j]])
                bests[sz] = i,j
                
        trySize = self.n
        while True:
            if bests[trySize]:
                # Figure out potential square start points
                y,x = bests[trySize]
                i = y-trySize+1
                j = x-trySize+1
                if self.isSquare(i, j, trySize ):
                    return (i,j,trySize)
            trySize -= 1
            if trySize<1:
                break
        return None
                
    def isSquare(self, i, j, sz):
        for x in range(sz):
            for y in range(sz):
                if self[i+y, j+x]==' ':
                    return False
        return True


    



