from __future__ import annotations

class Node:
    def __init__(self, name: str, prev: Node, next: Node):
        self.name = name
        self.next = next
        self.prev = prev

def insert(head: Node, tail: Node, name: str, left_numbers, disctionaries_node: dict):
    new_node: Node = Node(name, None, None)
    disctionaries_node[name]  = new_node

    temp = head
    if left_numbers == "M":
        tail.next = new_node
        new_node.prev = tail
        tail = new_node

    elif left_numbers == 0:
        new_node.next = head
        head.prev = new_node
        head = new_node

    else:
        for _ in range(left_numbers - 1):
            temp = temp.next

        next_temp = temp.next
        temp.next = new_node
        new_node.prev = temp
        new_node.next = next_temp
        if next_temp is not None:
            next_temp.prev = new_node
        else:
            tail = new_node

    return head, tail, disctionaries_node

def depart(head, tail, name, nodes):
    temp = nodes.pop(name)         

    if temp.prev is not None:
        temp.prev.next = temp.next
    else:
        head = temp.next           

    if temp.next is not None:
        temp.next.prev = temp.prev
    else:
        tail = temp.prev           

    temp.prev = temp.next = None
    return head, tail, nodes


def relocate(head, tail, name, displacement, nodes):
    if displacement == 0:
        return head, tail, nodes

    target = nodes[name]   

    old_prev = target.prev
    old_next = target.next

    if old_prev is not None:
        old_prev.next = old_next
    else:
        head = old_next
    if old_next is not None:
        old_next.prev = old_prev
    else:
        tail = old_prev
    target.prev = target.next = None

    if displacement > 0:
        current = old_next
        for _ in range(displacement - 1):
            current = current.next
        nxt = current.next
        current.next = target
        target.prev = current
        target.next = nxt
        if nxt is not None:
            nxt.prev = target
        else:
            tail = target
    else:
        current = old_prev
        for _ in range(-displacement - 1):
            current = current.prev
        prev = current.prev
        target.next = current
        current.prev = target
        target.prev = prev
        if prev is not None:
            prev.next = target
        else:
            head = target

    return head, tail, nodes


def show_result(head: Node):
    temp: Node = head
    while temp != None:
        print(temp.name, end=" ")
        temp = temp.next
    print()

def initialize_node(people_count: int):
    disctionaries_node: dict = {}

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

        disctionaries_node[new_node.name] = new_node
        
    return head, prev, disctionaries_node

def main():
    people_count, orders_count = map(int, input().split())

    head, tail, disctionaries_node = initialize_node(people_count)

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
            head, tail, disctionaries_node = insert(head, tail, name, position, disctionaries_node)

        elif command == "depart":
            name = line[1]
            head, tail, disctionaries_node = depart(head, tail, name, disctionaries_node)

        elif command == "relocate":
            name = line[1]
            displacement = int(line[2])
            head, tail, disctionaries_node = relocate(head, tail, name, displacement,disctionaries_node)
    show_result(head=head)


if __name__ == "__main__":
    main()