key = list(input("What is the key? ").lower())

playfair_matrix = [[False for i in range(5)] for j in range(5)]
position_dict = {chr(x):False for x in range(97, 123)}
position_dict.pop('j')

i, j = 0, 0
for x in key:
   if x == 'j':
       x = 'i'
   if position_dict[x] == False:
       playfair_matrix[i][j] = x
       position_dict[x] = (i, j)
       j = j + 1
       if j == 5 :
           j = 0
           i = i + 1
           if i == 5:
               break

if playfair_matrix[-1][-1] == False:
   for x in range(97, 123):
       x = chr(x)
       if x == 'j' :
           continue
       if position_dict[x] == False:
           playfair_matrix[i][j] = x
           position_dict[x] = (i, j)
           j = j + 1
           if j == 5 :
               j = 0
               i = i + 1
               if i == 5:
                   break

print("PLAYFAIR MATRIX -> ")
for i in range(5):
   print(" ".join(playfair_matrix[i]))

text = list(input("What's the plaintext? ").replace(" ", "").replace("j", "i"))
prev = text[0]
for i in range(1, len(text)) :
   if text[i] == prev :
       text.insert(i, 'z') #Adding fillers
   prev = text[i]

if len(text)%2 != 0 :
   text.append('z')

output = []
for i in range(0, len(text), 2) :
   a, b = text[i], text[i+1]
   posa, posb = position_dict[a], position_dict[b]

   #checking for same row
   if posa[0] == posb[0] :
       output.append(playfair_matrix[posa[0]][(posa[1] + 1)%5])
       output.append(playfair_matrix[posb[0]][(posb[1] + 1)%5])
  
   #checking for same column
   elif posa[1] == posb[1] :
       output.append(playfair_matrix[(posa[0] + 1)%5][posa[1]])
       output.append(playfair_matrix[(posb[0] + 1)%5][posb[1]])

   else:
       output.append(playfair_matrix[posa[0]][posb[1]])
       output.append(playfair_matrix[posb[0]][posa[1]])

print("Ciphertext:", "".join(output))

text = list("".join(output).replace(" ", ""))   

output = []
for i in range(0, len(text), 2) :
   a, b = text[i], text[i+1]
   posa, posb = position_dict[a], position_dict[b]

   #checking for same row
   if posa[0] == posb[0] :
       output.append(playfair_matrix[posa[0]][(posa[1] - 1)%5])
       output.append(playfair_matrix[posb[0]][(posb[1] - 1)%5])
  
   #checking for same column
   elif posa[1] == posb[1] :
       output.append(playfair_matrix[(posa[0] - 1)%5][posa[1]])
       output.append(playfair_matrix[(posb[0] - 1)%5][posb[1]])

   else:
       output.append(playfair_matrix[posa[0]][posb[1]])
       output.append(playfair_matrix[posb[0]][posa[1]])

print("Plaintext:", "".join(output))
