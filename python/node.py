from state import State
import numpy
import copy, numpy, math

class Node(object):
	def __init__(self, state, root, parent):
		self._state = state
		if parent == None:
			self._root = self
		else:
			self._root = root
		self._parent = parent
		self._children = None
		self._score = 0
		self._exp = 0

	def	setChildren(self):
		self._children = list([])
		for col in self._state.getAvailableCols():
			new_state = copy.deepcopy(self._state)
			if new_state._lastPlayer == 1:
				new_state.play(col, 2)
			else:
				new_state.play(col, 1)
			self._children.append(Node(new_state, self._root, self))
		
	def	updateScore(self, score):
		self._score += score
	
	def	updateExp(self):
		self._exp += 1
	
	def	getChildren(self):
		return self._children
	
	def	getScore(self):
		return self._score

	def	getExp(self):
		return self._exp

	def	getUcb1(self):
		if self._exp > 0:
			exploitation = self._score / self._exp
			exploration = 21 * math.sqrt(2) * math.sqrt(math.log(self._root.getExp()) / self._exp)
			return exploitation + exploration
		return math.inf
	

# board = numpy.full(shape=(6, 7), fill_value=0, dtype='b')
# state = State(board)
# root = Node(state, None, None)
# root.setChildren()
# print(root)
# print(root._root)
# for child in root._children:
# 	print("child:", child)
# 	print("childs root", child._root)
