import matplotlib.pyplot as plt

N = [2, 5, 20, 100, 500, 1000]
t_values = [0.01, 0.1, 0.3, 0.5]


param_time_t001 = [0.02, 0.15, 0.42, 3.30, 51.50, 321.0]
param_time_N1000 = [321.0, 42.0, 18.0, 11.0]

matrix_time_t001 = [0.76, 3.30, 37.50, 260.00, 4850.0, 21260.0]
matrix_time_N1000 = [21260.0, 4330.0, 3020.0, 2665.0]


plt.figure(figsize=(10, 6))

plt.plot(N, param_time_t001, color='red', marker='o', linewidth=2, label='Параметричний спосіб')
plt.plot(N, matrix_time_t001, color='blue', marker='s', linewidth=2, label='Матричний спосіб')

plt.yscale('log')
plt.xscale('log')

plt.title('Вплив кількості контрольних точок (N) на час побудови кривої\n(фіксований крок t = 0.01)', fontsize=14)
plt.xlabel('Кількість точок N (логарифмічна шкала)', fontsize=12)
plt.ylabel('Час, мс (логарифмічна шкала)', fontsize=12)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=12)
plt.tight_layout()

plt.savefig('Graph_1_Time_vs_N.png', dpi=300)
plt.close()


plt.figure(figsize=(10, 6))

plt.plot(t_values, param_time_N1000, color='red', marker='o', linewidth=2, label='Параметричний спосіб')
plt.plot(t_values, matrix_time_N1000, color='blue', marker='s', linewidth=2, label='Матричний спосіб')

plt.yscale('log')

plt.title('Вплив деталізації кроку (t) на час побудови кривої\n(фіксована кількість точок N = 1000)', fontsize=14)
plt.xlabel('Крок параметра t', fontsize=12)
plt.ylabel('Час, мс (логарифмічна шкала)', fontsize=12)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=12)
plt.tight_layout()

plt.savefig('Graph_2_Time_vs_t.png', dpi=300)
plt.close()

print("Успіх! Графіки збережено як PNG файли.")