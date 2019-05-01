class Stack:
    def __init__(self):
        self.__stack = []

    def size(self):
        return len(self.__stack)
    
    def is_empty(self):
        return self.size() == 0

    def is_full(self):
        return False
        
    def push(self, data):
        self.__stack.append(data)

    def pop(self):
        if not self.is_empty():
            return self.__stack.pop()

    def peek(self):
        if not self.is_empty():
            return self.__stack[self.size() - 1]
            