import random
from colorama import Fore, Style

# Function to simulate rolling a die 1000 times
def roll_dice(n=1000):
    face_counts = {i: 0 for i in range(1, 7)}  # Initialize counts for each face

    for _ in range(n):
        x = random.random()  # Generate a random number between 0 and 1
        
        # Determine dice face based on probability intervals
        if 0 < x < 1/6:
            face_counts[1] += 1
        elif 1/6 <= x < 2/6:
            face_counts[2] += 1
        elif 2/6 <= x < 3/6:
            face_counts[3] += 1
        elif 3/6 <= x < 4/6:
            face_counts[4] += 1
        elif 4/6 <= x < 5/6:
            face_counts[5] += 1
        else:
            face_counts[6] += 1

    return face_counts

# Run the simulation
results = roll_dice()

# Print the table with colors
print(f"\n{Fore.BLUE}Dice Rolling Simulation - 1000 Rolls{Style.RESET_ALL}\n")
print(f"{Fore.YELLOW}{'Face':<10}{'Frequency':<15}{'Percentage'}{Style.RESET_ALL}")
print(Fore.CYAN + "-" * 35 + Style.RESET_ALL)

total_rolls = sum(results.values())

for face, count in results.items():
    percentage = (count / total_rolls) * 100
    print(f"{Fore.GREEN}{face:<10}{count:<15}{percentage:.1f}%{Style.RESET_ALL}")

print(Fore.CYAN + "-" * 35 + Style.RESET_ALL)
print(f"{Fore.RED}{'Total':<10}{total_rolls:<15}{100.0}%{Style.RESET_ALL}")
