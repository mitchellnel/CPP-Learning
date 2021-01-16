"""
grid.py
Plot_py

Grid library interface and implementation

(Project adapted from C++ implementation)
"""

MAX_ROWS = 30
MAX_COLS = 30


class Grid:
    def __init__(self):
        self.nRows = 0
        self.nCols = 0

        self.GRID = None

    def set_size(self, nr, nc):
        if nr < 1 or nr > MAX_ROWS:
            print("Grid.set_size: invalid number of rows " + str(nr))
            exit(1)

        if nc < 1 or nc > MAX_COLS:
            print("Grid.set_size: invalid number of columns " + str(nc))
            exit(1)

        self.nRows = nr
        self.nCols = nc
        self.GRID = list()

        self.clear_grid()

    def get_rows(self):
        return self.nRows

    def get_cols(self):
        return self.nCols

    def clear_grid(self):
        if self.GRID is None:
            print("Grid.clear_grid: You must first call Grid.set_size().")

        self.GRID = [['x' for col in range(self.nCols)] for row in range(self.nRows)]

    def set_char(self, r, c, ch):
        self.check_pos(r, c, "set_char")
        self.GRID[r-1][c-1] = ch

    def get_char(self, r, c):
        self.check_pos(r, c, "get_char")
        return self.GRID[r-1][c-1]

    def draw(self):
        # Print column numbers in vertical form
        if self.nCols >= 10:
            print("   ", end="")
            for col in range(1, self.nCols+1):
                t = col / 10
                t = int(t)
                if t == 0:
                    print(' ', end="")
                else:
                    print(str(t), end="")
            print()

        print("   ", end="")

        for col in range(1, self.nCols+1):
            print(str(col % 10), end="")
        print()

        # Draw grid
        self.draw_horiz_border()

        for row in range(1, self.nRows+1):
            # Print row numbers
            print("{:>2}".format(row) + '|', end="")

            for col in range(1, self.nCols+1):
                ch = self.GRID[row-1][col-1]

                if ch.isprintable():
                    print(ch, end="")
                else:
                    print('?', end="")

            print('|')

        self.draw_horiz_border()

    def draw_horiz_border(self):
        print("  +", end="")

        for col in range(1, self.nCols+1):
            print('-', end="")

        print('+')

    def check_pos(self, r, c, func):
        if self.GRID is None:
            print("Grid.{0}: You must first call Grid.set_size().".format(func))
            exit(1)

        if r < 1 or r > self.nRows or c < 1 or c > self.nCols:
            print("Grid.{0}: invalid position ({1}, {2})".format(func, r, c))
            exit(1)
