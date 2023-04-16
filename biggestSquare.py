
if __name__=='__main__':
    from testData import data
    for x in data:
        b = x.biggest()
        print("============================")
        if b:
            print("biggest is %s at (%s,%s)" % (b[2], b[0], b[1]))
        else:
            print("Nothing - empty grid?")
        print(x)
    



