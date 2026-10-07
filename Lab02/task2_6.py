import random


def miller_rabin(n: int, k: int = 40) -> bool:
    if n < 2: return False
    if n in (2, 3): return True
    if n % 2 == 0: return False

    s, d = 0, n - 1
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        
        composite = True
        for _ in range(s - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                composite = False
                break
        if composite:
            return False
            
    return True

def generate_random_prime(bits: int) -> int:
    while True:
        p = random.randint(2**(bits - 1), 2**bits - 1)
        if p % 2 == 0:
            p += 1
        if miller_rabin(p):
            return p

def find_10_primes_below_M10():
    M10 = (2 ** 89) - 1
    primes = []
    candidate = M10 - 1 if (M10 - 1) % 2 != 0 else M10 - 2
    
    while len(primes) < 10:
        if miller_rabin(candidate):
            primes.append(candidate)
        candidate -= 2
    return M10, primes

def euclid_gcd(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b
    return a

def modular_exponentiation(base: int, exp: int, mod: int) -> int:
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp = exp // 2
        base = (base * base) % mod
    return result


if __name__ == "__main__":
    print("==================================================")
    print("1.1. SINH SỐ NGUYÊN TỐ NGẪU NHIÊN")
    print("==================================================")
    print(f"Số nguyên tố  8-bit : {generate_random_prime(8)}")
    print(f"Số nguyên tố 16-bit : {generate_random_prime(16)}")
    print(f"Số nguyên tố 64-bit : {generate_random_prime(64)}")
    
    print("\n==================================================")
    print("1.2. 10 SỐ NGUYÊN TỐ LỚN NHẤT NHỎ HƠN M10 (2^89 - 1)")
    print("==================================================")
    M10, top10_primes = find_10_primes_below_M10()
    print(f"Số Mersenne thứ 10 (M10) = {M10}")
    print("10 số nguyên tố lớn nhất liền trước M10:")
    for idx, p in enumerate(top10_primes, 1):
        print(f"  {idx:2d}. {p}")

    print("\n==================================================")
    print("2. ƯỚC SỐ CHUNG LỚN NHẤT (EUCLID GCD)")
    print("==================================================")
    num1 = 1234567891011121314151617181920
    num2 = 987654321098765432109876543210
    print(f"Số A = {num1}")
    print(f"Số B = {num2}")
    print(f"GCD(A, B) = {euclid_gcd(num1, num2)}")

    print("\n==================================================")
    print("3. LŨY THỪA MODULE VỚI SỐ MŨ LỚN")
    print("==================================================")
    base, exp, mod = 7, 40, 19
    res = modular_exponentiation(base, exp, mod)
    print(f"Yêu cầu: Tính {base}^{exp} mod {mod}")
    print(f"Kết quả thuật toán tự cài đặt     : {res}")
    print(f"Kiểm tra lại bằng hàm pow() có sẵn: {pow(base, exp, mod)}")
