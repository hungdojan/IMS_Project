import pygame
import os

W_WIDTH=700
W_HEIGHT=700
HEIGHT=100
WIDTH=100
HEADER=['// generated by pixel_editor app\n',
        '#include "board_setup.h"\n', 
        '\n', 
        'char INIT_POS[] = {\n',
        '};\n\n',
        '/* board_setup.c */\n'
]

# defining values
CHAR_VALUES=[' ', 'x', 'o']
COLORS=[(255, 255, 255),    # white
        (0, 0, 0),          # black
        (255, 0, 0)         # red
]


def load_startup_pos(filename: str) -> list[list[int]]:
    """Loads data from file.

    Parameters:
        filename (str): Path to source file.

    Returns:
        list[list[int]]: 2D list with data.
    """
    l = []
    with open(filename, 'r') as f:
        while not f.readline().startswith(HEADER[2]):
            pass
        f.readline()
        while True:
            line = f.readline()
            if line.startswith('}'):
                break;
            row = [convert_to_int(d.strip('\''))
                   for d in line.strip().split(',')[0:-1]]
            l.append(row)
    return l

def convert_to_char(i: int) -> str | None:
    """Converts int board value into char.

    Parameters:
        i (int): Integer board value.

    Returns:
        str: Equivalent character value.
    """
    try:
        return CHAR_VALUES[i]
    except IndexError:
        return None

def convert_to_int(c: str) -> int | None:
    """Converts char board value into int.

    Parameters:
        c (str): Character board value.

    Returns:
        int: Equivalent integer value.
    """
    return CHAR_VALUES.index(c)


def save_to_file(filename: str, data: list[list[int]]):
    """Save board into file.

    Parameters:
        filename (str): Path to destination file.
        data (list[list[int]]): Board data.
    """
    with open(filename, 'w') as f:
        f.write(HEADER[0])
        f.write(HEADER[1])
        f.write(HEADER[2])
        f.write(HEADER[3])
        for row in data:
            f.write('    ')
            for col in row:
                c = convert_to_char(col)
                f.write(f'\'{c}\',')
            f.write('\n')

        f.write(HEADER[-2])
        f.write(HEADER[-1])

def draw_board(screen: pygame.surface.Surface, data: list[list[int]]):
    """Draw UI for user to edit initial board used by another application."""
    rect_width = W_WIDTH / WIDTH
    rect_height = W_HEIGHT / HEIGHT
    for i, row in enumerate(data):
        for j, col in enumerate(row):
            pygame.draw.rect(screen, COLORS[col], pygame.Rect(rect_width * j, rect_height * i,rect_width, rect_height))

if __name__ == "__main__":
# init app
    pygame.init()
    screen = pygame.display.set_mode((W_WIDTH, W_HEIGHT))
    pygame.display.set_caption('Pixel maker')

    if not os.path.exists('board_setup.c'):
        # create empty list
        board = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    else:
        # load from 
        board = load_startup_pos('board_setup.c')

    running = True

    while running:
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            # keyboard event
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    running = False
                if event.key == pygame.K_c:
                    board = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]

            # mouse event
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_press = pygame.mouse.get_pressed()
                # get mouse coordinates
                pos = pygame.mouse.get_pos()
                x, y = pos[0] // (W_WIDTH // WIDTH), pos[1] // (W_HEIGHT // HEIGHT)
                # left button
                if mouse_press[0]:
                    board[y][x] = (board[y][x] + 1) % len(CHAR_VALUES)
                # right button
                if mouse_press[2]:
                    board[y][x] = (board[y][x] - 1) % len(CHAR_VALUES)


        draw_board(screen, board)
        pygame.display.update()

# close data
    save_to_file('board_setup.c', board)
    pygame.quit()