from __future__ import annotations

class Node:
    def __init__(self,prev_node: Node, next_node: Node, value: int):
        slef.prev = prev_node
        self.next = next_node
        self.value = value
    
def get_input():
    numbers_count, operation_count = map(int, input())
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
    return head, search_node

