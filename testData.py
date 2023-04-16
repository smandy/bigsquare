
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


lines7 = """
          |
 XX       |
 XXXX     |
  XXXXX   |
  XXXXX   |
   XXXX   |
   XXXX   |
          |
          |
          |
"""


lines8 = """
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
"""

lines9 = """
          |
          |
          |
          |
          |
          |
          |
          |
          |
          |
"""


lines10 = """
X         |
 XX       |
 XX       |
   XXX    |
   XXX    |
   XXX    |
      XXXX|
      XXXX|
      XXXX|
      XXXX|
"""


lines11 = """
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXX XXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
XXXXXXXXXX|
"""


from grid import Grid

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

data = [ parseSquare(x) for x in [lines1,
                                  lines2,
                                  lines3,
                                  lines4,
                                  lines5,
                                  lines6,
                                  lines7,
                                  lines8,
                                  lines9,
                                  lines10,
                                  lines11]]
