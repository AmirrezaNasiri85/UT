from __future__ import annotations

class Node:
    def __init__(self,prev_node: Node, next_node: Node, value: int):
        self.prev = prev_node
        self.next = next_node
        self.value = value
    
def get_input():
    numbers_count, operation_count = map(int, input().split())
    numbers: list = list(map(int, input().split()))

    head: Node = None
    prev: Node = None
    search_node: dict = {}
    for _ in range(numbers_count):
        new_node: Node = Node(prev, None, numbers[_])

        if head is None:
            head = new_node
        if prev is not None:
            prev.next = new_node

        search_node[new_node.value] = new_node
        prev = new_node
    return head, search_node, operation_count

def main_proccess(head: Node, search_node: dict, start_clip: int,
    end_clip: int, start_match: int):

    start_node: Node = search_node[start_clip]
    end_node: Node = search_node[end_clip]

    prev_node: Node = start_node.prev
    next_node: Node = end_node.next

    if prev_node is not None:
        prev_node.next = next_node
    if next_node is not None:
        next_node.prev = prev_node
    
    if start_node == head:
        head = next_node

    if start_match == 0:
        end_node.next = head
        start_node.prev = None
        if head is not None:
            head.prev = end_node
        head = start_node
    else:
        match_node: Node = search_node[start_match]
        next_after_match: Node = match_node.next

        match_node.next = start_node
        start_node.prev = match_node

        end_node.next = next_after_match
        if next_after_match is not None:
            next_after_match.prev = end_node
    
    return head, search_node


def show_result(head: Node):
    temp: Node = head
    while (temp != None):
        print(temp.value, end=" ")
        temp = temp.next
    print()

def sys_handel(haed: Node, search_node: dict, operation_count: int):
    for _ in range(operation_count):
        start_clip, end_clip, start_match = map(int, input().split())

        haed, search_node = main_proccess(haed, search_node, start_clip, end_clip, start_match)
    show_result(haed)
    
if __name__ == "__main__":
    head, search_node, operation_count = get_input()
    sys_handel(head, search_node, operation_count)
