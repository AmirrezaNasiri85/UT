def get_input():
    rows, columns = map(int, input().split(" "))
    field: list = []
    for row in range(rows):
        row_path: list = list(input())
        field.append(row_path)

    directions: str = input()

    return rows, columns, field, directions

def cordination_check(cordinate_x: int, cordinate_y: int, rows: int, columns: int) -> bool:
    if cordinate_x >= rows or cordinate_x < 0:
        print("False x")
        return False
    elif cordinate_y >= columns or cordinate_y < 0:
        print("False y")
        return False
    return True

def main_proccess(rows: int, columns: int, field: list, directions: str):
    REACHED = False
    movement_count = 0
    taken_candy = 0
    current_x = 0
    current_y = 0
    for move in directions:
        movement_count += 1

        if move == "R":
            if field[current_x][current_y + 1] != "#" and current_y + 1 < columns and current_y + 1 >= 0:
                current_y += 1
                if field[current_x][current_y] == "S":
                    field[current_x][current_y] = "."
                    taken_candy += 1

        elif move == "L":
            if field[current_x][current_y - 1] != "#" and current_y - 1 < columns and current_y - 1 >= 0:
                current_y -= 1
                if field[current_x][current_y] == "S":
                    field[current_x][current_y] = "."
                    taken_candy += 1

        elif move == "U":
            if field[current_x - 1][current_y] != "#" and current_x - 1 < rows and current_x - 1 >= 0:
                current_x -= 1
                if field[current_x][current_y] == "S":
                    field[current_x][current_y] = "."
                    taken_candy += 1

        elif move == "D":
            if field[current_x + 1][current_y] != "#" and current_x + 1 < rows and current_x + 1 >= 0:
                current_x += 1
                if field[current_x][current_y] == "S":
                    field[current_x][current_y] = "."
                    taken_candy += 1

        if field[current_x][current_y] == "B":
            REACHED = True
            break
    if REACHED:
        print("REACHED")
        print(f"{taken_candy} {movement_count}")
    else:
        print("LOST")
        print(f"{taken_candy} {current_x + 1} {current_y + 1}")
    
rows, columns, field, directions = get_input()
main_proccess(rows, columns, field, directions)