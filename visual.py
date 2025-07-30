import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

plt.style.use("dark_background")

def update(frame):
    line.set_data(x[:frame], y[:frame])
    line.set_3d_properties(z[:frame])
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
map = plt.figure(figsize=(10,9))
axis = map.add_subplot(111, projection='3d')
axis.set_xlim([-30, 30])
axis.set_ylim([-30, 30])
axis.set_zlim([-30, 30])
axis.set_xlabel('X')
axis.set_ylabel('Y')
axis.set_zlabel('Z')
axis.scatter(bomb_x, bomb_y, bomb_z, c='red', marker='o', label='Bombs')
axis.scatter([tx], [ty], [tz], c='gold', marker='*', s=100, label='Treasure')
line, = axis.plot([], [], [], color='blue', label='Your Path', linewidth=3)
animation = FuncAnimation(map, update, frames=len(x), interval=50, blit=True)
axis.legend()
plt.show()
