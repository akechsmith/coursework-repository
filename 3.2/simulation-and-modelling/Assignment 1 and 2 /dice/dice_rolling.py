import random

# Function to simulate rolling a die
def roll_dice(n=1000):
    face_counts = {i: 0 for i in range(1, 7)}

    for _ in range(n):
        x = random.random()
        
        if x < 1/6:
            face_counts[1] += 1
        elif x < 2/6:
            face_counts[2] += 1
        elif x < 3/6:
            face_counts[3] += 1
        elif x < 4/6:
            face_counts[4] += 1
        elif x < 5/6:
            face_counts[5] += 1
        else:
            face_counts[6] += 1

    return face_counts

# Run the simulation
results = roll_dice()

# Color codes
RED = "\033[31m"
RESET = "\033[0m"

# Print colored table
print(f"\n{RED}Dice Rolling Simulation - 1000 Rolls{RESET}\n")
print(f"{RED}{'Face':<10}{'Frequency':<15}{'Percentage'}{RESET}")
print(RED + "-" * 35 + RESET)

total_rolls = sum(results.values())

for face, count in sorted(results.items()):
    percentage = (count / total_rolls) * 100
    print(f"{RED}{face:<10}{count:<15}{percentage:.1f}%{RESET}")

print(RED + "-" * 35 + RESET)
print(f"{RED}{'Total':<10}{total_rolls:<15}{100.0:.1f}%{RESET}")