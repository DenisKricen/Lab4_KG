import matplotlib.pyplot as plt
import numpy as np

t_values = np.array([0.01, 0.1, 0.3, 0.5])
N_values = np.array([2, 5, 20, 100, 500, 1000])

X, Y = np.meshgrid(t_values, N_values)

Z_param = np.array([
    [0.02, 0.01, 0.01, 0.008],
    [0.15, 0.02, 0.01, 0.008],
    [0.42, 0.05, 0.03, 0.015],
    [3.30, 0.35, 0.17, 0.09],
    [51.50, 5.80, 2.50, 1.50],
    [321.0, 42.0, 18.0, 11.0]
])

Z_matrix = np.array([
    [0.76, 0.11, 0.07, 0.05],
    [3.30, 0.35, 0.20, 0.12],
    [37.50, 4.50, 2.20, 1.45],
    [260.00, 95.00, 54.00, 34.00],
    [4850.0, 750.0, 475.0, 370.0],
    [21260.0, 4330.0, 3020.0, 2665.0]
])

fig = plt.figure(figsize=(16, 7))

ax1 = fig.add_subplot(121, projection='3d')
surf1 = ax1.plot_surface(X, Y, Z_param, cmap='Reds', edgecolor='black', alpha=0.8)

ax1.set_title('Параметричний метод: Час $O(N)$', fontsize=14, pad=20)
ax1.set_xlabel('Крок параметра (t)', fontsize=12, labelpad=10)
ax1.set_ylabel('Кількість точок (N)', fontsize=12, labelpad=10)
ax1.set_zlabel('Час (мс)', fontsize=12, labelpad=10)
ax1.view_init(elev=25, azim=-135) 

ax2 = fig.add_subplot(122, projection='3d')
surf2 = ax2.plot_surface(X, Y, Z_matrix, cmap='Blues', edgecolor='black', alpha=0.8)

ax2.set_title('Матричний метод: Час $O(N^2)$', fontsize=14, pad=20)
ax2.set_xlabel('Крок параметра (t)', fontsize=12, labelpad=10)
ax2.set_ylabel('Кількість точок (N)', fontsize=12, labelpad=10)
ax2.set_zlabel('Час (мс)', fontsize=12, labelpad=10)
ax2.view_init(elev=25, azim=-135)

plt.suptitle('Комплексний вплив параметрів N та t на швидкість відмальовки кривої Безьє', fontsize=16, y=0.95)

plt.tight_layout()
plt.savefig('3D_Complexity_Comparison.png', dpi=300, bbox_inches='tight')
plt.close()

print("Готово! 3D графік збережено як 3D_Complexity_Comparison.png")