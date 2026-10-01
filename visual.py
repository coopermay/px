import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

plt.style.use("dark_background")

# the game treats y as up/down, but matplotlib draws the third axis vertically,
# so every point is plotted as (x, z, y)
def update(frame):
    line.set_data(x[:frame + 1], z[:frame + 1])
    line.set_3d_properties(y[:frame + 1])
    return line,

x = []
y = []
z = []

with open("path_data.txt") as f:
    for line in f:
        xi, yi, zi = map(int, line.strip().split())
        x.append(xi)
        y.append(yi)
        z.append(zi)
bomb_x, bomb_y, bomb_z = [], [], []
with open("bombs.txt") as f:
    for line in f:
        bx, by, bz = map(int, line.strip().split())
        bomb_x.append(bx)
        bomb_y.append(by)
        bomb_z.append(bz)
with open("treasure.txt", "r") as f:
    tx, ty, tz = map(int, f.readline().strip().split())
figure = plt.figure(figsize=(10,9))
axis = figure.add_subplot(111, projection='3d')
axis.set_xlim([-30, 30])
axis.set_ylim([-30, 30])
axis.set_zlim([-30, 30])
axis.set_xlabel('X')
axis.set_ylabel('Z')
axis.set_zlabel('Y (up)')
axis.scatter(bomb_x, bomb_z, bomb_y, c='red', marker='o', label='Bombs')
axis.scatter([tx], [tz], [ty], c='gold', marker='*', s=100, label='Treasure')
axis.scatter([0], [0], [0], c='white', marker='o', s=40, label='Start')
line, = axis.plot([], [], [], color='blue', label='Your Path', linewidth=3)
animation = FuncAnimation(figure, update, frames=max(len(x), 1), interval=50, blit=True)
axis.legend()
plt.show()
