""" A graphical user interface for creating Stickers.

Usage:
1. Click down on any point you would like to start drawing on
2. Hold and move your mouse to select any points you want to select.
3. The system is binary based, meaning each pixel you touch will flip once you touch it. For example, a black pixel
    will turn white once you click over it, while a white pixel will turn black
4. To save and exit, close the GUI window. *** DO NOT [ctrl-C] TERMINATE, AS THIS WILL NOT SAVE YOUR IMAGE ***
"""

from __future__ import annotations
import pygame
import numpy as np

SIZE = 25
input_filename = None
save_filename = "out.txt"

# Set up the screen
background_colour = (255, 255, 255)
width, height = 900, 900
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Sticker!')

screen.fill(background_colour)

WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)

start_x, start_y = width // 2, height // 2


def find_particle(particles, x, y):
    for p in particles:
        if p.x_range[0] <= x <= p.x_range[1] and p.y_range[0] <= y <= p.y_range[1]:
            return p


class Particle:
    def __init__(self, center: tuple, spacing: int):
        self.center_x = center[0]
        self.center_y = center[1]
        self.selected = True
        self.spacing = spacing
        self.x_range = (self.center_x - spacing // 2, self.center_x + spacing // 2)
        self.y_range = (self.center_y - spacing // 2, self.center_y + spacing // 2)
        self.lock = False

    def display(self):
        sides = [
            (self.center_x + self.spacing // 2, self.center_y + self.spacing // 2),
            (self.center_x + self.spacing // 2, self.center_y - self.spacing // 2),
            (self.center_x - self.spacing // 2, self.center_y - self.spacing // 2),
            (self.center_x - self.spacing // 2, self.center_y + self.spacing // 2)
        ]
        if self.selected:
            pygame.draw.polygon(screen, BLACK, sides, 0)
        else:
            pygame.draw.polygon(screen, BLACK, sides, 5)


# Main code
def main():
    spacing = width // SIZE
    start = spacing // 2
    my_particles = [Particle((start + i * spacing, start + j * spacing), spacing) for i in range(SIZE) for j in range(SIZE)]

    if input_filename is not None:
        preset_data(my_particles)

    selected_particle = None
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        mouse_keys = pygame.mouse.get_pressed()
        if mouse_keys[0]:  # mouse down
            mouseX, mouseY = pygame.mouse.get_pos()
            selected_particle = find_particle(my_particles, mouseX, mouseY)
        elif selected_particle is not None:  # release mouse
            for part in my_particles:
                part.lock = False
            selected_particle = None

        if selected_particle is not None and not selected_particle.lock:
            selected_particle.selected = not selected_particle.selected
            selected_particle.lock = True

        screen.fill(background_colour)

        for particle in my_particles:
            particle.display()

        pygame.display.flip()

    arr = [["0" for _ in range(SIZE)] for __ in range(SIZE)]
    x_pos = 0
    y_pos = 0
    for part in my_particles:
        if not part.selected:
            arr[x_pos][y_pos] = "1"
        else:
            arr[x_pos][y_pos] = "0"

        if x_pos >= SIZE - 1:
            x_pos = 0
            y_pos += 1
        else:
            x_pos += 1

    arr = ["".join(item) for item in arr]
    file = open(save_filename, 'w')
    file.write("\n".join(arr))
    file.close()


def preset_data(my_particles):
    assert isinstance(input_filename, str)
    read = np.load(input_filename)
    n = 0
    for i in range(read.shape[0]):
        for j in range(read.shape[1]):
            if not read[j][i] == 1:
                my_particles[n].selected = False
            n += 1


if __name__ == "__main__":
    main()
