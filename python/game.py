import numpy as np

class State:
	def __init__(self, board):
		self._board = board
		self._lastCol = -1
		self._lastRow = -1
		self._lastPlayer = -1

	# Setting methods
	def	setLastPos(self, col):
		print(self._board)
		self._lastCol = col
		row = 0
		while (row < 6 and self._board[row][self._lastCol] == 0):
			row += 1
		if (row == 6):
			row -= 1
		self._lastRow = row
		self._validMousePos = True

	def setLastPlayer(self):
		self._lastPlayer = self._board[self._lastRow][self._lastCol]

	# Pygame methods
	def	setMousePos(self, click_pos, player):
		if (45 < click_pos[0] and click_pos[0] < 115):
			self.play(0, player)
		elif (135 < click_pos[0] and click_pos[0] < 205):
			self.play(1, player)
		elif (225 < click_pos[0] and click_pos[0] < 295):
			self.play(2, player)
		elif (315 < click_pos[0] and click_pos[0] < 385):
			self.play(3, player)
		elif (405 < click_pos[0] and click_pos[0] < 475):
			self.play(4, player)
		elif (495 < click_pos[0] and click_pos[0] < 565):
			self.play(5, player)
		elif (585 < click_pos[0] and click_pos[0] < 655):
			self.play(6, player)
		else:
			self._validMousePos = False

	def	isValidMousePos(self):
		return (self._validMousePos)
	
	def	getTokPos(self):
		x = 9 + (self._lastCol * 90)
		y = 430 - ((5 - self._lastRow) * 80)
		return ((x, y))

	# Game methods
	def	isAvailable(self, col):
		if (self._board[0][col] == 0):
			return (True)

	def	play(self, col, player):
		i = 0
		if (self.isAvailable(col)):
			while (i < 6 and self._board[i][col] == 0):
				i += 1
			self._board[i - 1][col] = player
		else:
			print("Illegal move.")
		self.setLastPos(col)
		self.setLastPlayer()

	def	isWin(self):
		if (self._lastCol == -1):
			return (False)
		if (self.isWinCol() or self.isWinRow() or self.isWinDiag()):
			return (True)
		return (False)

	def isWinCol(self):
		if (self._lastRow > 2):
			return (False)
		count = 0
		row = self._lastRow
		while (row < self._lastRow + 4 and
		self._board[row][self._lastCol] == self._lastPlayer):
			count += 1
			row += 1
		if (count == 4):
			return (True)
		return (False)

	def isWinRow(self):
		count = 0
		col = max(0, self._lastCol - 3)
		# print(self._lastRow)
		while (col < min(6, self._lastCol + 3)):
			if (self._board[self._lastRow][col] == self._lastPlayer):
				count += 1
			else:
				count = 0
			if (count == 4):
				return (True)
			col += 1
		return (False)

	def isWinDiag(self):
		if (self.isWinDiagDown() or self.isWinDiagUp()):
			return (True)

	def isWinDiagDown(self):
		count = 0
		row = self._lastRow
		col = self._lastCol
		i = 0
		while (i < 4 and row > 0 and col > 0):
			row -= 1
			col -= 1
			i += 1
		while (row < min(6, self._lastRow + 4) and col < min(7, self._lastCol + 4)):
			if (self._board[row][col] == self._lastPlayer):
				count += 1
			else:
				count = 0
			if (count == 4):
				return (True)
			row += 1
			col += 1
		return (False)

	def isWinDiagUp(self):
		count = 0
		row = self._lastRow
		col = self._lastCol
		i = 0
		while (i < 4 and row < 5 and col > 0):
			row += 1
			col -= 1
			i += 1
		while (row > max(0, self._lastRow - 4) and col < min(7, self._lastCol + 4)):
			if (self._board[row][col] == self._lastPlayer):
				count += 1
			else:
				count = 0
			if (count == 4):
				return (True)
			row -= 1
			col += 1
		return (False)

	def	isDraw(self):
		return (True)

	# Getting methods
	def getBoard(self):
		return (self._board)

# board = np.full(shape=(6, 7), fill_value=0, dtype='b')
# state = State(board)
# state.play(0, 2)
# state.play(1, 2)
# state.play(2, 1)
# state.play(3, 2)
# state.play(3, 2)
# state.play(5, 2)
# state.play(4, 1)
# state.play(0, 2)
# state.play(1, 2)
# state.play(2, 2)
# state.play(3, 1)
# state.play(3, 2)
# state.play(5, 2)
# state.play(4, 1)
# state.play(0, 2)
# state.play(1, 1)
# state.play(2, 2)
# state.play(4, 1)
# state.play(0, 1)
# state.play(0, 1)
# state.play(1, 2)
# state.play(0, 1)
# state.play(1, 2)
# state.play(0, 1)
# state.play(1, 2)
# state.play(0, 1)

# print("lastCol", state.lastCol)
# print("lastRow", state.lastRow)
# print(state.getBoard())
# print(state.isWinCol())