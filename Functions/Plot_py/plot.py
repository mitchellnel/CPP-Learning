"""
plot.py
Plot_py

Plotting function implementation

(Project adapted from C++ implementation)
"""

import grid as gr
import command_processing as cp

HORIZ = 0
VERT = 1

FG = 0
BG = 1


def main():
    plot_grid = gr.Grid()

    plot_grid.set_size(20, 30)

    current_char = '*'
    current_mode = FG

    while True:
        command_string = input("Enter a command string: ")

        if command_string == "":
            break

        position = -1
        status = 0

        if status == 0:
            plot_grid.draw()
        elif status == 1:
            print("Syntax error at position {0}".format(position + 1))
        elif status == 2:
            print("Cannot perform command at string position {0}".format(position + 1))
        else:
            # It should be impossible to get here
            print("performCommands returned an invalid status {0}!".format(status))


if __name__ == "__main__":
    main()