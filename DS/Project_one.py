# Getting input
def get_input():
    rows, columns,  repeat_count = map(int, input().split())

    shape_input: list = []
    for _ in range(rows):
        new_input: list = list(input())
        shape_input.append(new_input)

    return rows, columns, repeat_count, shape_input

# Printing the result base on th eoutput of the answer.
def print_result(given_shape: list):
    for row in given_shape:
        for obj in row:
            print(obj, end="")
        print()

# Main procces function.
def main_proccess(rows : int, columns: int, repeat_count: int, given_shape: list):
    result_shape: list = []
    for row_index in range(rows):
        
        new_shape: list = []
        for column_index in range(columns):
            chose_obj = given_shape[row_index][column_index]

            new_shape.extend([chose_obj] * repeat_count)
        result_shape.extend([new_shape] * repeat_count)
    
    print_result(result_shape)


# Starting operation.
# rows, columns, repeat_count, given_shape = get_input()
# main_proccess(rows, columns, repeat_count, given_shape)


def main_proccess_2(rows : int, columns: int, repeat_count: int, given_shape: list):
    result_shape: list = []
    for row_index in range(rows):
        new_shape: str = ""
        for column_index in range(columns):
            new_shape += (repeat_count * given_shape[row_index][column_index])
        
    

