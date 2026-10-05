def get_input():
    numbers_count = int(input())

    b_list = list(map(int, input().split(' ')))
    
    return numbers_count, b_list

def print_result(b_list: list):
    for obj in b_list:
        print(obj, end=" ")
    print()


def main_proccess(numbers_count: int, b_list: list):
    result_list: list = []
    for start_number in range(1, b_list[0]):
        cuurent_value = start_number
        result_list.append(cuurent_value)
        for b_obj in b_list:
            next_number = b_obj - cuurent_value
            if next_number <= 0:
                result_list.clear()
                break
            elif next_number in result_list:
                result_list.clear()
                break
            result_list.append(next_number)
            cuurent_value = next_number 

        if(len(result_list) == numbers_count):
            print_result(result_list)
            break
        else:
            result_list.clear()

numbers_count, b_list = get_input()
main_proccess(numbers_count, b_list)
