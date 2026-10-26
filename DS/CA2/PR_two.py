def get_input():
    numbers_count: int = int(input())
    numbers_list: list = list(map(int, input().split()))

    return numbers_count, numbers_list


def main_procces(count: int, numbers_list: list):
    stack = []      
    result = 0
    for i, x in enumerate(numbers_list):
        while stack and numbers_list[stack[-1]] < x:
            stack.pop()
            result += 1

        if stack and numbers_list[stack[-1]] == x:
            result += 1
            stack.pop()
        elif stack:
            result += 1

        stack.append(i)
    return result
  
if __name__ == "__main__":
    count, numbers_list = get_input()
    result = main_procces(count,numbers_list)
    print(result)
