class Wardrobe:
    def __init__(self, id: str, is_locked, items: list, total_sum: int, total_items: int):
        self.total_sum = 0
        self.total_items = 0
        self.id = id
        self.is_locked = is_locked
        self.items = items

class Wardrobe_handeler():
    def __init__(self, wardrobe_dict: dict):
        self.wardrobe_dict = wardrobe_dict

    def NEW(self, id: str):
        try:
            if id in self.wardrobe_dict:
                raise KeyError
            new_wardrode = Wardrobe(id, False, [], 0, 0)
            self.wardrobe_dict[id] = new_wardrode

        except KeyError as error:
            print("DuplicateLocker")
        
    def PUT(self, id: str, value: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrode: Wardrobe = self.wardrobe_dict[id]
            if target_wardrode.is_locked:
                raise TypeError
            elif value <= 0:
                raise ValueError  
            target_wardrode.items.append(value)
            target_wardrode.total_items += 1
            target_wardrode.total_sum += value

        except KeyError as error:
            print("LockerNotFound")
        except TypeError as error:
            print("LockerIsLocked")
        except ValueError as error:
            print("InvalidValue")
    
    def LOCK(self, id: str):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            targte_wardrone: Wardrobe = self.wardrobe_dict[id]
            targte_wardrone.is_locked = True

        except KeyError as error:
            print("LockerNotFound")

    def GET(self, id: str, index: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrone: Wardrobe = self.wardrobe_dict[id]
            if target_wardrone.is_locked:
                raise TypeError
            elif index >= len(target_wardrone.items):
                raise IndexError
            print(target_wardrone.items[index])
        except KeyError as error:
            print("LockerNotFound")
        except TypeError as error:
            print("LockerIsLocked")
        except IndexError as error:
            print("IndexOutOfRange")
        
    def AVG(self, id: str):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrone: Wardrobe = self.wardrobe_dict[id]
            if target_wardrone.is_locked:
                raise TypeError
            elif not target_wardrone.items:
                raise ZeroDivisionError
            print(target_wardrone.total_sum // target_wardrone.total_items)
        
        except KeyError as error:
            print("LockerNotFound")
        except TypeError as error:
            print("LockerIsLocked")
        except ZeroDivisionError as error:
            print("EmptyLocker")
    def MERGE(self, id1: str, id2: str):
        try:
            if (id1 not in self.wardrobe_dict) or (id2 not in self.wardrobe_dict):
                raise KeyError
            elif id1 == id2:
                raise ValueError
            target_one: Wardrobe = self.wardrobe_dict[id1]
            target_two: Wardrobe = self.wardrobe_dict[id2]
    
            if (target_one.is_locked) or (target_two.is_locked):
                raise TypeError
            merged_list = target_two.items
            target_one.items += merged_list
            target_one.total_items += target_two.total_items
            target_one.total_sum += target_two.total_sum
            del self.wardrobe_dict[id2]

        except KeyError as error:
            print("LockerNotFound")
        except ValueError as error:
            print("SameLocker")
        except TypeError as error:
            print("LockerIsLocked")
    
    def EXIT(self):
        self.wardrobe_dict.clear()

def main_procces():
    sys_manager: Wardrobe_handeler = Wardrobe_handeler({})
    while True:
        line_input: list = list(input().split())

        if(line_input[0] == "NEW"):
            sys_manager.NEW(line_input[1])
        elif(line_input[0] == "PUT"):
            sys_manager.PUT(line_input[1], int(line_input[2]))
        elif(line_input[0] == "LOCK"):
            sys_manager.LOCK(line_input[1])
        elif(line_input[0] == "GET"):
            sys_manager.GET(line_input[1], int(line_input[2]))
        elif(line_input[0] == "AVG"):
            sys_manager.AVG(line_input[1])
        elif(line_input[0] == "MERGE"):
            sys_manager.MERGE(line_input[1], line_input[2])
        elif(line_input[0] == "EXIT"):
            sys_manager.EXIT()
            break
main_procces()
