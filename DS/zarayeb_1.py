def give_input():
    list_a: list = list(map(int, input().split()))
    list_b: list = list(map(int, input().split()))

    return list_a, list_b

def main_proccess(list_a: list, list_b: list):
    lists_length = len(list_a)

    result: list = [0]  * (2 * lists_length - 1)

    for index_one in range(lists_length):
        for index_two in range(lists_length):
            result[index_one + index_two] += list_a[index_one] * list_b[index_two]

    print(result)

main_proccess([1, 2, 3, 4], [2, 3, 4, 1])
