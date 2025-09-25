import heapq
from collections import deque

def print_puzzle(puzzle):
    size = int(len(puzzle) ** 0.5)
    for i in range(size):
        print(" ".join(str(puzzle[i * size + j]) if puzzle[i * size + j] != 0 else ' ' for j in range(size)))
    print()

def is_solvable(puzzle):
    inv_count = sum(
        1 for i in range(len(puzzle)) for j in range(i + 1, len(puzzle))
        if puzzle[i] and puzzle[j] and puzzle[i] > puzzle[j]
    )
    return inv_count % 2 == 0

def bfs(puzzle, goal):
    queue = deque([(puzzle, [])])
    visited = set()
    while queue:
        state, path = queue.popleft()
        if state == goal:
            return path
        visited.add(tuple(state))
        for move, new_state in get_successors(state):
            if tuple(new_state) not in visited:
                queue.append((new_state, path + [move]))
    return []

def dfs(puzzle, goal, depth_limit=20):
    def recursive_dfs(state, path, depth):
        if state == goal:
            return path
        if depth >= depth_limit:
            return None
        for move, new_state in get_successors(state):
            result = recursive_dfs(new_state, path + [move], depth + 1)
            if result:
                return result
        return None
    return recursive_dfs(puzzle, [], 0)

def a_star(puzzle, goal, heuristic):
    heap = [(heuristic(puzzle, goal), 0, puzzle, [])]
    visited = set()
    while heap:
        _, cost, state, path = heapq.heappop(heap)
        if state == goal:
            return path
        visited.add(tuple(state))
        for move, new_state in get_successors(state):
            if tuple(new_state) not in visited:
                heapq.heappush(heap, (cost + 1 + heuristic(new_state, goal), cost + 1, new_state, path + [move]))
    return []

def count_wrong(state, goal):
    return sum(1 for i in range(len(state)) if state[i] != goal[i] and state[i] != 0)

def manhattan_distance(state, goal):
    size = int(len(state) ** 0.5)
    return sum(
        abs((state.index(i) // size) - (goal.index(i) // size)) +
        abs((state.index(i) % size) - (goal.index(i) % size))
        for i in range(1, len(state))
    )

def get_successors(state):
    size = int(len(state) ** 0.5)
    zero_index = state.index(0)
    row, col = divmod(zero_index, size)
    moves = []
    if row > 0:  # Up
        moves.append((-size, 'Up'))
    if row < size - 1:  # Down
        moves.append((size, 'Down'))
    if col > 0:  # Left
        moves.append((-1, 'Left'))
    if col < size - 1:  # Right
        moves.append((1, 'Right'))
    
    successors = []
    for move, move_name in moves:
        new_state = state[:]
        new_state[zero_index], new_state[zero_index + move] = new_state[zero_index + move], new_state[zero_index]
        successors.append((move_name, new_state))
    return successors

def animate_solution(puzzle, solution):
    state = puzzle[:]
    print("Awal:")
    print_puzzle(state)
    for move in solution:
        print(f"Langkah: {move}")
        state = apply_move(state, move)
        print_puzzle(state)

def apply_move(state, move):
    size = int(len(state) ** 0.5)
    zero_index = state.index(0)
    if move == "Up":
        swap_index = zero_index - size
    elif move == "Down":
        swap_index = zero_index + size
    elif move == "Left":
        swap_index = zero_index - 1
    elif move == "Right":
        swap_index = zero_index + 1
    state = state[:]
    state[zero_index], state[swap_index] = state[swap_index], state[zero_index]
    return state

def solve_8puzzle(puzzle):
    goal = list(range(1, len(puzzle))) + [0]
    if not is_solvable(puzzle):
        print("The entered puzzle is not solvable.")
        return
    
    print("Puzzle Awal:")
    print_puzzle(puzzle)

    print("Solving with BFS...")
    bfs_solution = bfs(puzzle, goal)
    print("BFS Solution:", bfs_solution)
    animate_solution(puzzle, bfs_solution)

    print("\nSolving with DFID...")
    dfs_solution = dfs(puzzle, goal)
    print("DFID Solution:", dfs_solution)
    animate_solution(puzzle, dfs_solution)

    print("\nSolving with A* (Hamming)...")
    astar_hamming_solution = a_star(puzzle, goal, count_wrong)
    print("A* (Hamming) Solution:", astar_hamming_solution)
    animate_solution(puzzle, astar_hamming_solution)

    print("\nSolving with A* (Manhattan)...")
    astar_manhattan_solution = a_star(puzzle, goal, manhattan_distance)
    print("A* (Manhattan) Solution:", astar_manhattan_solution)
    animate_solution(puzzle, astar_manhattan_solution)

# Example puzzle (3x3)
puzzle_example = [5, 4, 0, 6, 1, 8, 7, 3, 2]
solve_8puzzle(puzzle_example)
