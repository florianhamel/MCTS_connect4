import datetime

tab = list([0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
for i in range(1000000):
	rand = datetime.datetime.now().microsecond
	tab[rand % 10] += 1
print(tab)
print(datetime.datetime.now())
