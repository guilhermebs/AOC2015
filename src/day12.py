import json


def sum_values_dict(obj):
    result = 0
    for k, v in obj.items():
        if k == "red" or v == "red":
            return 0
        if isinstance(k, int):
            result += k
        if isinstance(v, dict):
            result += sum_values_dict(v)
        elif isinstance(v, int):
            result += v
        elif isinstance(v, list):
            result += sum_values_list(v)
    return result


def sum_values_list(obj):
    result = 0
    for e in obj:
        if isinstance(e, int):
            result += e
        elif isinstance(e, dict):
            result += sum_values_dict(e)
        elif isinstance(e, list):
            result += sum_values_list(e)
    return result


def solve():
    contents = open("inputs/day12").read()
    obj = json.loads(contents)#contents)
    print(sum_values_dict(obj))


if __name__ == "__main__":
    solve()