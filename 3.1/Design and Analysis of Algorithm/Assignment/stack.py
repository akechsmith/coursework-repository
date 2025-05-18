import tkinter as tk
from tkinter import messagebox

class CandyDispenserApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Candy Dispenser with Spring")
        self.candies = []
        self.max_size = 7

        # Create the UI elements
        self.label = tk.Label(self.root, text="Enter candy (e.g., Red, Blue):")
        self.label.pack(pady=5)

        self.entry = tk.Entry(self.root)
        self.entry.pack(pady=5)

        self.push_button = tk.Button(self.root, text="Push", command=self.push_candy)
        self.push_button.pack(pady=5)

        self.pop_button = tk.Button(self.root, text="Pop", command=self.pop_candy)
        self.pop_button.pack(pady=5)

        self.top_button = tk.Button(self.root, text="Peek (Top)", command=self.top_candy)
        self.top_button.pack(pady=5)

        self.is_empty_button = tk.Button(self.root, text="Is Empty?", command=self.is_empty)
        self.is_empty_button.pack(pady=5)

        self.len_button = tk.Button(self.root, text="Size", command=self.candy_count)
        self.len_button.pack(pady=5)

        # Add a frame around the dispenser
        self.dispenser_frame = tk.Frame(self.root, bg="darkblue", padx=10, pady=10)
        self.dispenser_frame.pack(pady=10)

        # Dispenser Canvas (increased size)
        self.canvas = tk.Canvas(self.dispenser_frame, width=300, height=650, bg="lightblue", highlightthickness=2, highlightbackground="black")
        self.canvas.pack()

        self.update_dispenser_display()

    def update_dispenser_display(self):
        # Clear the canvas
        self.canvas.delete("all")

        # Draw the spring
        self.draw_spring()

        # Draw candies from bottom to top
        candy_width = 100  # Width for the oval candies
        candy_height = 50  # Height for the oval candies
        base_y = 580  # Moved higher to fit the spring and candies properly
        spacing = 60  # Spacing between candies
        for index, candy in enumerate(self.candies):
            x_center, y_center = 150, base_y - (index + 1) * spacing
            x1, y1 = x_center - candy_width // 2, y_center - candy_height // 2
            x2, y2 = x_center + candy_width // 2, y_center + candy_height // 2
            self.canvas.create_oval(x1, y1, x2, y2, fill="pink", outline="black", width=2)
            self.canvas.create_text(x_center, y_center, text=candy, font=("Helvetica", 12))

    def draw_spring(self):
        # Draw a conical spring at the bottom of the dispenser
        base_x, base_y = 150, 580  # Adjusted base center of the spring
        top_y = 500  # Adjusted top height of the spring
        num_turns = 10  # Number of coils in the spring
        radius_start, radius_end = 90, 40  # Base and top radius of the spring

        for i in range(num_turns + 1):
            t = i / num_turns
            radius = radius_start + t * (radius_end - radius_start)
            y = base_y - t * (base_y - top_y)
            self.canvas.create_oval(base_x - radius, y, base_x + radius, y + 2, fill="gray", outline="gray")

    def spring_animation(self, operation):
        # Animate the spring for compression (push) and decompression (pop)
        if operation == "add":
            for _ in range(5):
                self.canvas.move("all", 0, -2)
                self.root.update()
                self.canvas.move("all", 0, 2)
                self.root.update()
        elif operation == "remove":
            for _ in range(5):
                self.canvas.move("all", 0, 2)
                self.root.update()
                self.canvas.move("all", 0, -2)
                self.root.update()

    def push_candy(self):
        candy = self.entry.get()
        if len(self.candies) >= self.max_size:
            messagebox.showerror("Error", "Dispenser is full!")
        elif candy:
            self.candies.append(candy)
            self.spring_animation("add")
            self.update_dispenser_display()
            self.entry.delete(0, tk.END)
        else:
            messagebox.showerror("Error", "Please enter a candy name")

    def pop_candy(self):
        if len(self.candies) == 0:
            messagebox.showerror("Error", "Dispenser is empty!")
        else:
            removed_candy = self.candies.pop()
            self.spring_animation("remove")
            messagebox.showinfo("Candy Removed", f"You removed: {removed_candy}")
            self.update_dispenser_display()

    def top_candy(self):
        if len(self.candies) == 0:
            messagebox.showerror("Error", "Dispenser is empty!")
        else:
            top_candy = self.candies[-1]
            messagebox.showinfo("Top Candy", f"The top candy is: {top_candy}")

    def is_empty(self):
        if len(self.candies) == 0:
            messagebox.showinfo("Is Empty", "The dispenser is empty")
        else:
            messagebox.showinfo("Is Empty", "The dispenser is not empty")

    def candy_count(self):
        count = len(self.candies)
        messagebox.showinfo("Candy Count", f"There are {count} candies in the dispenser")

# Run the application
root = tk.Tk()
app = CandyDispenserApp(root)
root.mainloop()
