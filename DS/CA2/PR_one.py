from collections import deque

def get_input():
    input_count: int = int(input())
    numbers_list: list = list(map(int, input().split()))

    return input_count, numbers_list

def main_procces(input_count: int, numbers_list: list):
    index_orders: list = []
    pre_index = deque(range(len(numbers_list)))
    recommendation: list = [0] * input_count
    
    step = 0
    while len(pre_index) != 0:
        if step == 0:
            element = pre_index.popleft()
            index_orders.append(element)
            step += 1
        else:
            element = pre_index.popleft()
            pre_index.append(element)
            step = 0
    
    target_index: int = 0
    numbers_list.sort()
    for index in index_orders:
        recommendation[index] = numbers_list[target_index]
        target_index += 1

    return recommendation

def print_result(recommendation: list):
    for obj in recommendation:
        print(obj, end=" ")
    print()

if __name__ == "__main__":
    input_count, numbers_list = get_input()
    result: list = main_procces(input_count, numbers_list)
    print_result(result)