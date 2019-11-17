# MCTS_connect4
An implementation of the Monte Carlo Tree Search algorithm on the Connect 4 game in C.

It is a simplified version of the Reinforcement Learning algorithm used by AlphaGo. The algorithm provides the best move to play at a state S of a game, with 4 principal steps:

- Selection: select the most interesting node with the help of the UCB1 formula - each node is associated with a state.
- Simulation: simulate a game with random moves from the best looking node previously selected and get a value depending on the outcome: a win, a loss or a draw.
- Backpropagation: backpropagate the value obtained with the simulation
- Expansion: create new children for the node selected if it doesn't have children yet and it has been visited already.

The MCTS algorithm is based on the Law of Large Numbers, it finds the best move to play with a confidence interval depending on the number of simulations. That means that contrary to Minimax algorithm, there is not need to check all the nodes, because the best move to play is statistically calculated. As a consequence, the computing time is drastically reduced for an outcome almost as good as the Minimax one.
