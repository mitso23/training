
def testIterations():
    words = ['cat', 'window', 'door']
    #Take a copy of the words before
    for word in words[: ]:
        if word == 'window' :
            print("Equal")
            words.append("hese")
        print(word);

    for i in range(len(words)) :
        print("i: ", i , "data: ", words[i])