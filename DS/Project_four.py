class Wardrobe:
    def __init__(self, id: int, is_locked, items: list):
        self.id = id
        self.is_locked = is_locked
        self.items = items

class Wardrobe_handeler():
    def __init__(self, wardrobe_dict: dict):
        self.wardrobe_dict = wardrobe_dict

    def NEW(self, id: int):
        try:
            if id in self.wardrobe_dict:
                raise KeyError
            new_wardrode = Wardrobe(id, False, [])
            self.wardrobe_dict[id] = new_wardrode

        except KeyError as error:
            return("DuplicateLocker")
        
    def PUT(self, id: int, value: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrode: Wardrobe = self.wardrobe_dict[id]
            if target_wardrode.is_locked:
                raise TypeError
            elif value <= 0:
                raise ValueError  
            target_wardrode.items.append(value)

        except KeyError as error:
            return("LockerNotFound")
        except TypeError as error:
            return("LockerIsLocked")
        except ValueError as error:
            return("InvalidValue")
    
    def LOCK(self, id: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            targte_wardrone: Wardrobe = self.wardrobe_dict[id]
            targte_wardrone.is_locked = True

        except KeyError as error:
            return("LockerNotFound")

    def GET(self, id: int, index: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrone: Wardrobe = self.wardrobe_dict[id]
            if target_wardrone.is_locked:
                raise TypeError
            elif index >= len(target_wardrone.items):
                raise IndexError
            return(target_wardrone.items[index])
        except KeyError as error:
            return("LockerNotFound")
        except TypeError as error:
            return("LockerIsLocked")
        except IndexError as error:
            return("IndexOutOfRange")
        
    def AVG(self, id: int):
        try:
            if id not in self.wardrobe_dict:
                raise KeyError
            target_wardrone: Wardrobe = self.wardrobe_dict[id]
            if target_wardrone.is_locked:
                raise TypeError
            elif not target_wardrone.items:
                raise ZeroDivisionError
            sum_weights = sum(target_wardrone.items)
            items_count = len(target_wardrone.items)
            return(sum_weights // items_count)
        
        except KeyError as error:
            return("LockerNotFound")
        except TypeError as error:
            return("LockerIsLocked")
        except ZeroDivisionError as error:
            return("EmptyLocker")
    def MERGE(self, id1: int, id2: int):
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
            del self.wardrobe_dict[id2]

        except KeyError as error:
            return("LockerNotFound")
        except ValueError as error:
            return("SameLocker")
        except TypeError as error:
            return("LockerIsLocked")
    
    def EXIT(self):
        self.wardrobe_dict.clear()


def print_result(out_puts: list):
    for obj in out_puts:
        if obj is not None:
            print(obj)

def main_procces():
    sys_manager: Wardrobe_handeler = Wardrobe_handeler({})
    out_puts: list = []
    while True:
        line_input: list = list(input().split())

        if(line_input[0] == "NEW"):
            out_puts.append(sys_manager.NEW(int(line_input[1])))
        elif(line_input[0] == "PUT"):
            out_puts.append(sys_manager.PUT(int(line_input[1]), int(line_input[2])))
        elif(line_input[0] == "LOCK"):
            out_puts.append(sys_manager.LOCK(int(line_input[1])))
        elif(line_input[0] == "GET"):
            out_puts.append(sys_manager.GET(int(line_input[1]), int(line_input[2])))
        elif(line_input[0] == "AVG"):
            out_puts.append(sys_manager.AVG(int(line_input[1])))
        elif(line_input[0] == "MERGE"):
            out_puts.append(sys_manager.MERGE(int(line_input[1]), int(line_input[2])))
        elif(line_input[0] == "EXIT"):
            out_puts.append(sys_manager.EXIT())
            break
    print_result(out_puts)
main_procces()
