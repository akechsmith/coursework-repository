from collections import deque
from tabulate import tabulate

# State Representation: (Man, Leopard, Goat, Grass)
# 0 = Left Bank, 1 = Right Bank
initial_state = (0, 0, 0, 0)  # All on the left bank
goal_state = (1, 1, 1, 1)     # All on the right bank

def is_valid_state(state):
    """Ensures the leopard is never left alone with the goat, and the goat is never left alone with the grass."""
    man, leopard, goat, grass = state
    # Goat must not be alone with leopard, and grass must not be alone with goat
    if (leopard == goat and goat != man) or (goat == grass and grass != man):
        return False
    return True

def get_neighbors(state):
    """Generates valid next states from the current state."""
    man, leopard, goat, grass = state
    neighbors = []
    
    # Possible moves: Man can travel alone or take one item
    possible_moves = [(0, 0, 0), (1, 0, 0), (0, 1, 0), (0, 0, 1)]  # (Leopard, Goat, Grass)

    for move in possible_moves:
        leopard_move, goat_move, grass_move = move

        # Move Man and the selected item(s) to the other side
        new_man = 1 - man  # Flip side
        new_leopard = leopard + leopard_move if man == 0 else leopard - leopard_move
        new_goat = goat + goat_move if man == 0 else goat - goat_move
        new_grass = grass + grass_move if man == 0 else grass - grass_move

        # Ensure all new positions are within valid bounds (0 or 1)
        if not (0 <= new_leopard <= 1 and 0 <= new_goat <= 1 and 0 <= new_grass <= 1):
            continue

        new_state = (new_man, new_leopard, new_goat, new_grass)
        if is_valid_state(new_state):
            neighbors.append(new_state)

    return neighbors

def bfs():
    """Performs BFS to find the shortest solution path."""
    queue = deque([(initial_state, [])])
    visited = set([initial_state])

    while queue:
        state, path = queue.popleft()

        if state == goal_state:
            return path + [state]

        for neighbor in get_neighbors(state):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [state]))

    return None  # No solution found

def get_move_description(from_state, to_state, move):
    """Generates a readable description of a move."""
    man_from, leopard_from, goat_from, grass_from = from_state
    man_to, leopard_to, goat_to, grass_to = to_state
    man_move, leopard_move, goat_move, grass_move = move

    actions = []
    if leopard_move:
        actions.append("Leopard")
    if goat_move:
        actions.append("Goat")
    if grass_move:
        actions.append("Grass")

    if not actions:
        return "Man crosses alone."

    action_str = ', '.join(actions)
    direction = "right" if man_from == 0 else "left"
    return f"Man takes {action_str} to the {direction} bank."

def print_solution(solution):
    """Formats and prints the solution using a table."""
    if solution:
        headers = ["Step", "Man", "Leopard", "Goat", "Grass", "Action"]
        table = []

        # Add the initial state with "Initial State" description
        table.append(["", solution[0][0], solution[0][1], solution[0][2], solution[0][3], "Initial State"])

        for i in range(len(solution) - 1):
            prev_state = solution[i]
            next_state = solution[i + 1]
            move = tuple(next_state[j] - prev_state[j] for j in range(4))
            action_description = get_move_description(prev_state, next_state, move)
            table.append([i + 1, next_state[0], next_state[1], next_state[2], next_state[3], action_description])

        # Add final goal state description
        table.append(["", solution[-1][0], solution[-1][1], solution[-1][2], solution[-1][3], "Reached goal state"])

        print("\nBFS Solution found:")
        print(tabulate(table, headers=headers, tablefmt="grid"))
    else:
        print("No solution found.")

# Run BFS to solve the puzzle
solution = bfs()

# Display the solution in a human-readable format
print_solution(solution)
