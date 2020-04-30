from game import State
import numpy as np
import sys, pygame, gc, time

def print_tokens(win, tokens):
    for token in tokens:
        win.blit(token[0], token[1])

def main():
    board = np.full(shape=(6, 7), fill_value=0, dtype='b')
    state = State(board)
    # print(state._board[5][6])
    player = 1
    pygame.init()
    size = 700, 540
    win = pygame.display.set_mode(size)
    board_game = pygame.image.load("connect4_board.png")
    board_game_rect = board_game.get_rect().move(30, 30)
    tokens = list([])
    while (not state.isWin()):
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()
        for click in pygame.mouse.get_pressed():
            if (click):
                state.setMousePos(pygame.mouse.get_pos(), player)
                if (state.isValidMousePos()):
                    if (player == 1):
                        red_tok = pygame.image.load("red_tok.png")
                        red_tok_rect = red_tok.get_rect().move(state.getTokPos())
                        tokens.append([red_tok, red_tok_rect])
                        player = 2
                        pygame.time.delay(200)
                    else:
                        yellow_tok = pygame.image.load("yellow_tok.png")
                        yellow_tok_rect = yellow_tok.get_rect().move(state.getTokPos())
                        tokens.append([yellow_tok, yellow_tok_rect])
                        player = 1
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