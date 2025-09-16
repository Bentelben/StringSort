filename = input("Enter filename: ")

ALLOWED_SYMBOLS = " "
for i in range(ord('a'), ord('z')+1):
    ALLOWED_SYMBOLS += chr(i)
for i in range(ord('A'), ord('Z')+1):
    ALLOWED_SYMBOLS += chr(i)
for i in range(ord('а'), ord('я')+1):
    ALLOWED_SYMBOLS += chr(i)
for i in range(ord('А'), ord('Я')+1):
    ALLOWED_SYMBOLS += chr(i)

infile = open(filename, 'r')
lines = infile.readlines()
infile.close()

outfile = open("output.txt", 'w', encoding='UTF-8')
for line_ref in lines:
    line = ""
    for symbol in line_ref:
        if symbol in ALLOWED_SYMBOLS:
            line += symbol

    line = line.strip()

    if line == '':
        continue

    outfile.write(line + "\n")


outfile.close()
