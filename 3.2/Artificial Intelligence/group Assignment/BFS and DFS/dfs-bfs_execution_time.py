import time
from BFS import bfs
from DFS import dfs

# Measure BFS
start = time.time()
bfs_solution = bfs()
print(f"BFS Time: {time.time() - start:.6f} sec")

# Measure DFS
start = time.time()
dfs_solution = dfs()
print(f"DFS Time: {time.time() - start:.6f} sec")