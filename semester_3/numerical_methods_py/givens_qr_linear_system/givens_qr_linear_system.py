import numpy as np

np.set_printoptions(precision=2, suppress=True)

A = np.array([
    [ 6,  0, -2,  0, -1],
    [ 0,  5,  0, -2,  0],
    [-2,  0,  4,  0, -1],
    [ 0, -2,  0,  3,  0],
    [-1,  0, -1,  0,  3],
], dtype=float)


def sqrt_method(A, b):
    n = len(A)
    R = A.copy()
    d = np.zeros(n)

    print("=== УСЛОВИЕ: решить систему A·x = b ===")
    print("Матрица A:")
    print(A)
    print("Вектор b:", b)

    print("\n=== ШАГ 1. Раскладываем A = Rᵀ·D·R ===")
    for i in range(n):
        taken = sum(d[k] * R[k, i] ** 2 for k in range(i))
        w = R[i, i] - taken
        d[i] = np.sign(w)
        R[i, i] = np.sqrt(abs(w))
        print(f"Строка {i+1}: ω = {A[i, i]:g} - {taken:.2f} = {w:.2f}, "
              f"d{i+1} = {d[i]:g}, r{i+1}{i+1} = √{abs(w):.2f} = {R[i, i]:.2f}")

        for j in range(i + 1, n):
            a_ij = R[i, j]
            ssum = sum(d[k] * R[k, i] * R[k, j] for k in range(i))
            R[i, j] = (a_ij - ssum) / (d[i] * R[i, i])
            if R[i, j] != 0:
                print(f"          r{i+1}{j+1} = ({a_ij:g} - {ssum:.2f}) / "
                      f"({d[i]:g}·{R[i, i]:.2f}) = {R[i, j]:.2f}")

    R = np.triu(R)
    print("\nМатрица R:")
    print(R)
    print("Диагональ D:", d)

    print("\n=== ШАГ 2. Прямой ход: Rᵀ·y = b ===")
    y = np.zeros(n)
    for i in range(n):
        y[i] = (b[i] - sum(R[k, i] * y[k] for k in range(i))) / R[i, i]
        print(f"y{i+1} = {y[i]:.2f}")
    print("Вектор y:", y)

    print("\n=== ШАГ 3. Обратный ход: R·x = D·y ===")
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        ssum = sum(R[i, k] * x[k] for k in range(i + 1, n))
        x[i] = (d[i] * y[i] - ssum) / R[i, i]
        print(f"x{i+1} = {x[i]:.2f}")

    print("\n=== ОТВЕТ ===")
    print("Вектор x =", x)
    return x


if __name__ == "__main__":
    if not np.allclose(A, A.T):
        raise SystemExit("Матрица не симметрична, метод не применим")

    b = np.array(list(map(float, input("Введите 5 чисел вектора b через пробел: ").split())))
    sqrt_method(A, b)