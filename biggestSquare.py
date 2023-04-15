
def partition(xs,n):
    ret = []
    while xs:
        xs, chunk = xs[n:], xs[:n]
        ret.append(chunk)
        #print(ret)
    return ret

import copy    

class Grid:
    def __init__(self, n):
        self.data = [' '] * ( n * n)
        self.n = n
    def idx(self, x):
        return x[0]*self.n + x[1]
    def __getitem__(self, x):
        return self.data[ self.idx(x)  ]
    def __setitem__(self, x, n):
        #print("Setitem %s %s" % (x,n))
        self.data[ self.idx(x) ] = n

    def __repr__(self):
        return "\n".join( [ "".join(x) for x in partition(self.data, self.n)  ] )

    def biggest(self):
        current = copy.deepcopy(self)
        best = None
        for i in range(self.n):
            for j in range(self.n):
                if current[i,j] not in ['X', ' ']:
                    # Visited square
                    #print("Continue at %s %s" % (i,j))
                    continue
                current, sz = current.biggestAt(i,j)
                #rint(current)
                if not best or sz>best[1]:
                    best = current, sz, i, j
        return best
    
    def biggestAt(self, i,j, doClone = False):
        #et = copy.deepcopy(self)
        ret = self
        #i,j = idx
        trySize = 0
        running = True
        while running:
            #print("Trying size %s" % trySize)
            for x in range(trySize+1):
                #ret[i+trySize, j +  trySize] = str(trySize)
                if j+trySize>= self.n or ret[i+x ,j+trySize] == ' ':
                    running = False
                    return ret, trySize
                if i + trySize>=self.n or ret[i+trySize,j+x] == ' ':
                    running = False
                    return ret, trySize
            # Successful check. Paint tiles
            for x in range(trySize+1):            
                ret[i+x,j+trySize] = str(trySize+1)
                ret[i+trySize,j+x] = str(trySize+1)
            trySize += 1
            #rint("Sz is now %s" % trySize)
        return ret, sz

lines1= """
   XXX    |
   XXX    |
   XXX    |
          |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
          |
"""


lines2 = """
   XXXX   |
   XXXX   |
   XXXX   |
   XXXX   |
          |
          |
          |
          |
          |
          |
"""

lines3  = """
   XXXX   |
   XXXX   |
   XXXX   |
   XXXX   |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
      XXX |
"""

lines4 = """
   XXXX   |
   XXXX   |
  XXXXX   |
  XXXXX   |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
    XXXXX |
      XXX |
"""

lines5 = """
     XX   |
     XX   |
  XX  X   |
  XX      |
  XXXXXXX |
  XXXXXXX |
  XXXXXXX |
  XXXXXXX |
  XXXXXXX |
  XXXXXXX |
"""

lines6 = """
          |
 XXXXXXX  |
  XXXXXXXX|
 XXXXXXXXX|
 XXXXXXXXX|
 XXXXXXXXX|
 XXXXXXXXX|
          |
          |
          |
"""



def parseSquare(x):
    """return list of lines, must be square"""
    lines = [ y[:-1] for y in x.split("\n")[1:-1]]
    #rint(len(lines))
    #rint( [len(x) for x in lines] )
    #rint( set([len(x) for x in lines]))
    s = set([ len(x) for x in lines])
    assert len(s)==1, "Malformed %s" % s
    assert list(s)[0]==len(lines), "Malformed %s vs %s" % (len(s), len(lines))
    ret = Grid(len(lines))
    for i, line in enumerate(lines):
        for j, x in enumerate(line):
            #print( (i,j,x))
            ret[i,j] = x
    return ret


for lines in [lines1, lines2, lines3, lines4, lines5, lines6]:
    x = parseSquare(lines)
    #print( x.biggestAt(0,3) )
    #print( x.biggestAt(0,0) )
    b = x.biggest()
    print(b[0])
    print( "Biggest square size %s at (%s,%s)" % b[1:] )



