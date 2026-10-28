from __future__ import annotations

class Node:
    def __init__(self, name: str, prev: Node, next: Node):
        self.name = name
        self.next = next
        self.prev = prev

def insert(head: Node, tail: Node, name: str, left_numbers):
    new_node: Node = Node(name, None, None)

    temp = head
    if left_numbers == "M":
        tail.next = new_node
        new_node.prev = tail
        tail = new_node
        return head, tail
    elif left_numbers == 0:
        new_node.next = head
        head.prev = new_node
        head = new_node
    else:
        for _ in range(left_numbers - 1):
            temp = temp.next
        next_temp: Node = temp.next
        temp.next = new_node
        new_node.prev = temp
        new_node.next = next_temp
        next_temp.prev = new_node
    return head, tail

def depart(head: Node, tail: Node, name: str):
    temp: Node = head  
    while(temp.name != name):
        temp = temp.next

    if(temp == head):
        new_head: Node = temp.next
        temp.prev = None
        head = new_head
        return head, tail
    elif(temp == tail):
        tail = tail.prev
        tail.next = None
        return head, tail

    
    prev: Node = temp.prev
    next: Node = temp.next

    prev.next = next
    if next is not None:
        next.prev = prev
    
    temp.next = None
    temp.prev = None

    return head

def relocate(head: Node, tail: Node, name: str, displacement: int):
    if displacement == 0 or head is None or head.next is None:
        return head

    target = head
    while target is not None and target.name != name:
        target = target.next

    if target is None:
        return head

    old_prev = target.prev
    old_next = target.next


    if target == head:
        head = target.next
        if head is not None:
            head.prev = None
    elif target == tail:
        tail = tail.prev
        if tail is not Node:
            tail.next = None
    else:
        if target.prev is not None:
            target.prev.next = target.next
        if target.next is not None:
            target.next.prev = target.prev

    target.prev = None
    target.next = None

    if displacement > 0:
        current = old_next if old_next is not None else head
        for _ in range(displacement - 1):
            if current.next is not None:
                current = current.next
        
        next = current.next
        current.next = target
        target.prev = current
        target.next = next
        if next is not None:
            next.prev = target
    else:
        current = old_prev if old_prev is not None else head
        for _ in range(-displacement - 1):
            if current.prev is not None:
                current = current.prev

        prev = current.prev
        target.next = current
        current.prev = target
        target.prev = prev
        if prev is not None:
            prev.next = target
        else:
            head = target

    return head
def show_result(head: Node):
    temp: Node = head
    while temp != None:
        print(temp.name, end=" ")
        temp = temp.next
    print()

def initialize_node(people_count: int):
    people: list = list(input().split())
    
    head: Node = None
    prev: Node = None
    for _ in people:
        new_node: Node = Node(_, None, None)
        if head is None:
            head = new_node
        if prev is not None:
            prev.next = new_node
        new_node.prev = prev
        prev = new_node
        
    return head, prev

def main():
    people_count, orders_count = map(int, input().split())

    head, tail = initialize_node(people_count)

    for _ in range(orders_count):
        line = input().split()
        if not line:
            continue
        command = line[0]

        if command == "insert":
            name = line[1]
            position = line[2]
            if position != "M":
                position = int(position)
            head, tail = insert(head, tail, name, position)

        elif command == "depart":
            name = line[1]
            head, tail = depart(head, tail, name)

        elif command == "relocate":
            name = line[1]
            displacement = int(line[2])
            head, tail = relocate(head, tail, name, displacement)
    show_result(head=head)


if __name__ == "__main__":
    main()
