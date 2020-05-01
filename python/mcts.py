from state import State
from node import Node
import copy, array, datetime, numpy, math, gc

class Mcts:
	def	__init__(self, root):
		self._root = root

	def	select(self):
		best_node = self._root
		while best_node.getChildren() != None:
			best_ucb1 = -math.inf
			for child in best_node.getChildren():
				child_ucb1 = child.getUcb1()
				if child_ucb1 > best_ucb1:
					best_ucb1 = child_ucb1
					best_node = child
		return best_node

	def	simulate(self, node):
		state_dup = copy.deepcopy(node._state)
		while True:
			avail_cols = state_dup.getAvailableCols()
			rand = datetime.datetime.now().microsecond % len(avail_cols)
			if state_dup._lastPlayer == 1:
				state_dup.play(avail_cols[rand], 2)
			else:
				state_dup.play(avail_cols[rand], 1)
			if state_dup.isWin():
				if state_dup.getLastPlayer() == 1:
					return state_dup.getScore()
				else:
					return -state_dup.getScore()
			if state_dup.isDraw():
				return 0

	def	expand(self, node):
		node.setChildren()

	def	backpropagate(self, node, score):
		while node != None:
			node.updateScore(score)
			node.updateExp()
			node = node._parent

	def	getBestCol(self):
		i = 0
		best_score = -math.inf
		for child in self._root.getChildren():
			child_score = child.getScore()
			print("child", i, " :", child.getScore())
			if child_score > best_score:
				best_score = child_score
				best_col = child._state.getLastCol()
			i += 1
		print()
		return best_col

	def	play(self, iter):
		self.expand(self._root)
		while iter > 0:
			best_node = self.select()
			if best_node._state.isWin() and best_node._state.getLastPlayer() == 2:
				best_node._parent._score = -math.inf
			elif best_node.getExp() == 0:
				score = self.simulate(best_node)
				self.backpropagate(best_node, score)
			else:
				self.expand(best_node)
				score = self.simulate(best_node.getChildren()[0])
				self.backpropagate(best_node.getChildren()[0], score)
			iter -= 1
		return self.getBestCol()


# board = numpy.full(shape=(6, 7), fill_value=0, dtype='b')
# state = State(board)
# root = Node(state, None, None)
# mcts = Mcts(root)
# print(mcts.play(6000))