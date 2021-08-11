import sys
import math



# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

class Node:
    def __init__(self, *args):
        if len(args) == 0:
            self.is_null = True
        else :
            self.x = args[0]
            self.y = args[1]
            self.character = args[2]
            self.prev = args[3]
            self.is_null = args[4]
    


def checkNeighbors(current, maze, nodes, visited):
    if maze[current.y-1][current.x] != '#' and not visited[current.y-1][current.x]:
        visited[current.y-1][current.x] = True
        nodes.append(Node(current.x, current.y-1, maze[current.y-1][current.x], current, False))
    
    if maze[current.y+1][current.x] != '#' and not(visited[current.y+1][current.x]):
        visited[current.y+1][current.x] = True
        nodes.append(Node(current.x, current.y+1, maze[current.y+1][current.x], current, False))
    
    if maze[current.y][current.x-1] != '#' and not(visited[current.y][current.x-1]):
        visited[current.y][current.x-1] = True
        nodes.append(Node(current.x-1, current.y, maze[current.y][current.x-1], current, False))
    
    if maze[current.y][current.x+1] != '#' and not(visited[current.y][current.x+1]):
        visited[current.y][current.x+1] = True
        nodes.append(Node(current.x+1, current.y, maze[current.y][current.x+1], current, False))
    

def get_next_node(current):
    if current.prev.is_null == True:
        return current

    return get_next_node(current.prev)

def bfs(maze, goal, rows, columns, start):

    tab_visited = []

    for index in range(rows):
        temp_array = []
        for num in range(columns):
            temp_array.append(False)
    
        tab_visited.append(temp_array)
    

    tab_visited[start.y][start.x] = True

    nodes = []
    it = 0
    nodes.append(start)

    while True: 
        checkNeighbors(nodes[it], maze, nodes, tab_visited)


        for i in range(it, len(nodes)):
            if nodes[i].character == goal:
                return get_next_node(nodes[i])
            
            i+=1

        it+=1

        if it > (len(nodes) - 1):
            break
        
    result = Node(0, 0, 'c', Node(), True)

    return result




# r: number of rows.
# c: number of columns.
# a: number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
r, c, a = [int(i) for i in input().split()]
control_reached = False
# game loop
while True:
    # kr: row where Kirk is located.
    # kc: column where Kirk is located.
    kr, kc = [int(i) for i in input().split()]

    labyrinth = []

    for i in range(r):
        row = input()  # C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
        labyrinth.append(row)

    
    first_node = Node(kc, kr, labyrinth[kr][kc], Node(), True)

    if labyrinth[kr][kc] == 'C':
        control_reached = True

    final_node = Node()

    if control_reached:
        final_node = bfs(labyrinth, 'T', r, c, first_node)
    else:
        final_node = bfs(labyrinth, '?', r, c, first_node)
        if final_node.is_null:
            final_node = bfs(labyrinth, 'C', r, c, first_node)

    if not final_node.is_null:
        if final_node.x > kc:
            print("RIGHT")
        elif final_node.x < kc:
            print("LEFT") 
        elif final_node.y > kr: 
            print("DOWN")
        else:
            print("UP")      
    else:
        print("final node null", file=sys.stderr, flush=True)
        

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)

    # Kirk's next move (UP DOWN LEFT or RIGHT).
    

