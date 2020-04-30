import numpy as np
import gc
from game import State

def	main():
	board = board = np.full(shape=(6, 7), fill_value=0, dtype='b')
	state = State(board)
	while (not state.isWin()):
		print(state.getBoard())
		col_p1 = int(input("joue: "))
		state.play(col_p1, 1)
		if (not state.isWin()):
			print(state.getBoard())
			col_p2 = int(input("joue: "))
			state.play(col_p2, 2)
		else:
			print(state.getBoard())
			print("p1 won")
			break
		test = gc.collect()
		print(test)

main()