from state import State
from node import Node
from mcts import Mcts
import numpy as np
import sys, pygame, gc, copy

def print_tokens(win, tokens):
    for token in tokens:
        win.blit(token[0], token[1])

def main():
    board = np.full(shape=(6, 7), fill_value=0, dtype='b')
    state = State(board)
    player = 1
    pygame.init()
    size = 700, 540
    win = pygame.display.set_mode(size)
    board_game = pygame.image.load("connect4_board.png")
    board_game_rect = board_game.get_rect().move(30, 30)
    tokens = list([])
    while not state.isWin():
        win.fill((255, 255, 255))
        print_tokens(win, tokens)
        win.blit(board_game, board_game_rect)
        pygame.display.flip()
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()
        for click in pygame.mouse.get_pressed():
            if player == 2 and click:
                state.setMousePos(pygame.mouse.get_pos(), player)
                if state.isValidMousePos():
                    red_tok = pygame.image.load("red_tok.png")
                    red_tok_rect = red_tok.get_rect().move(state.getTokPos())
                    tokens.append([red_tok, red_tok_rect])
                    player = 1
                    win.fill((255, 255, 255))
                    print_tokens(win, tokens)
                    win.blit(board_game, board_game_rect)
                    pygame.display.flip()
                    pygame.time.delay(50)
        if player == 1:
            root = Node(copy.deepcopy(state), None, None)
            mcts = Mcts(root)
            state.play(mcts.play(6000), 1)
            yellow_tok = pygame.image.load("yellow_tok.png")
            yellow_tok_rect = yellow_tok.get_rect().move(state.getTokPos())
            tokens.append([yellow_tok, yellow_tok_rect])
            player = 2
            pygame.time.delay(200)
        win.fill((255, 255, 255))
        print_tokens(win, tokens)
        win.blit(board_game, board_game_rect)
        pygame.display.flip()
        gc.collect()


main()

# 9, 350 -> down left - 1y pos
# 9, 430 -> down left pos
# ==> 80 dif between y
# 9, 430 -> down left pos
# 99, 430 -> down left -1x pos
# ==> 90 dif between x