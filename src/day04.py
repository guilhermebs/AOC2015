import hashlib


def solve():
    seed = "bgvyzdsv"
    i = 0
    while not hashlib.md5(f"{seed}{i}".encode()).hexdigest().startswith("000000"):
        i += 1
    print("Part 1 solution:", i)


if __name__ == "__main__":
    solve()