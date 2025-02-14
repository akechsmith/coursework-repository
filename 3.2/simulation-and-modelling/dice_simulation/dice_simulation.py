import sys
import random
import numpy as np
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QLabel, QTableWidget, QTableWidgetItem
)
from PyQt5.QtGui import QPixmap, QFont
from PyQt5.QtCore import Qt, QTimer
import matplotlib.pyplot as plt


class DiceRollingSimulation(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Dice Rolling Simulation")
        self.setGeometry(200, 200, 1000, 700)
        self.setStyleSheet("background-color: #f0f8ff; color: #003366;")

        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.title_label = QLabel("Dice Rolling Simulation")
        self.title_label.setFont(QFont("Verdana", 24, QFont.Bold))
        self.title_label.setAlignment(Qt.AlignCenter)
        self.title_label.setStyleSheet("color: #003366; padding: 10px;")
        self.layout.addWidget(self.title_label)

        self.roll_button = QPushButton("Roll Die")
        self.roll_button.setStyleSheet(
            """
            QPushButton {
                background-color: #0066cc;
                color: white;
                font-size: 18px;
                font-weight: bold;
                padding: 12px;
                border-radius: 15px;
                border: 2px solid #004d99;
            }
            QPushButton:hover {
                background-color: #005bb5;
            }
            QPushButton:pressed {
                background-color: #004080;
            }
            """
        )
        self.roll_button.clicked.connect(self.roll_dice)
        self.layout.addWidget(self.roll_button, alignment=Qt.AlignCenter)

        self.single_dice_label = QLabel()
        self.single_dice_label.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.single_dice_label)

        self.dice_faces_container = QWidget()
        self.dice_faces_layout = QHBoxLayout(self.dice_faces_container)
        self.dice_faces_layout.setSpacing(20)
        self.dice_faces_layout.setContentsMargins(0, 20, 0, 20)
        self.dice_faces_layout.setAlignment(Qt.AlignCenter)
        self.dice_faces_container.setVisible(False)
        self.layout.addWidget(self.dice_faces_container)

        self.dice_images = []
        self.frequency_labels = []
        for i in range(6):
            dice_container = QVBoxLayout()

            dice_image_label = QLabel()
            dice_image_label.setAlignment(Qt.AlignCenter)
            dice_container.addWidget(dice_image_label)
            self.dice_images.append(dice_image_label)

            frequency_label = QLabel(f"Face {i + 1}: 0 times")
            frequency_label.setFont(QFont("Verdana", 12))
            frequency_label.setAlignment(Qt.AlignCenter)
            dice_container.addWidget(frequency_label)
            self.frequency_labels.append(frequency_label)

            self.dice_faces_layout.addLayout(dice_container)

        self.result_table = QTableWidget()
        self.result_table.setColumnCount(3)
        self.result_table.setHorizontalHeaderLabels(["Face", "Frequency", "Percentage"])
        self.result_table.setStyleSheet(
            """
            QTableWidget {
                background-color: #e6f2ff;
                color: #003366;
                font-size: 14px;
                border: 1px solid #99ccff;
                gridline-color: #99ccff;
                selection-background-color: #99ccff;
                selection-color: #003366;
            }
            QHeaderView::section {
                background-color: #0066cc;
                color: white;
                font-size: 14px;
                padding: 4px;
            }
            QTableWidget::item {
                padding: 4px;
            }
            """
        )
        self.layout.addWidget(self.result_table)

        self.stats_button = QPushButton("Show Statistics")
        self.stats_button.setStyleSheet(
            """
            QPushButton {
                background-color: #008000;
                color: white;
                font-size: 18px;
                font-weight: bold;
                padding: 12px;
                border-radius: 15px;
                border: 2px solid #006600;
            }
            QPushButton:hover {
                background-color: #007000;
            }
            QPushButton:pressed {
                background-color: #005500;
            }
            """
        )
        self.stats_button.clicked.connect(self.display_chart)
        self.layout.addWidget(self.stats_button, alignment=Qt.AlignCenter)

    def roll_dice(self):
        self.dice_faces_container.setVisible(False)
        self.single_dice_label.show()

        self.rolls = np.random.randint(1, 7, size=1000)
        self.faces, self.counts = np.unique(self.rolls, return_counts=True)

        self.animate_dice()

    def animate_dice(self):
        pixmaps = [QPixmap(f"dice_{i + 1}.png") for i in range(6)]

        def randomize_image():
            self.single_dice_label.setPixmap(random.choice(pixmaps).scaled(150, 150, Qt.KeepAspectRatio))

        def finalize_results():
            self.single_dice_label.hide()
            self.dice_faces_container.setVisible(True)

            for face, count in zip(self.faces, self.counts):
                self.dice_images[face - 1].setPixmap(pixmaps[face - 1].scaled(100, 100, Qt.KeepAspectRatio))
                self.frequency_labels[face - 1].setText(f"Face {face}: {count} times")

            self.update_table()

        self.timer = QTimer(self)
        self.timer.timeout.connect(randomize_image)
        self.timer.start(50)
        QTimer.singleShot(1000, lambda: (self.timer.stop(), finalize_results()))

    def update_table(self):
        total_rolls = sum(self.counts)
        self.result_table.setRowCount(len(self.faces))
        for i, (face, count) in enumerate(zip(self.faces, self.counts)):
            percentage = (count / total_rolls) * 100
            self.result_table.setItem(i, 0, QTableWidgetItem(str(face)))
            self.result_table.setItem(i, 1, QTableWidgetItem(str(count)))
            self.result_table.setItem(i, 2, QTableWidgetItem(f"{percentage:.1f}%"))

    def display_chart(self):
        expected_frequency = 1000 / 6
        min_freq = min(self.counts)
        max_freq = max(self.counts)

        bars = plt.bar(self.faces, self.counts, color='#4da6ff', edgecolor='#003366', alpha=0.85)

        for bar, count in zip(bars, self.counts):
            plt.text(bar.get_x() + bar.get_width() / 2, bar.get_height() - 10, str(count),
                     ha='center', va='bottom', fontsize=10, fontweight='bold', color='#003366')

        plt.axhline(expected_frequency, color='red', linestyle='--', label='Expected Frequency (166.67)')
        plt.xlabel("Dice Face", fontsize=12, fontweight='bold', color='#003366')
        plt.ylabel("Frequency", fontsize=12, fontweight='bold', color='#003366')
        plt.title("Dice Roll Frequency Distribution", fontsize=14, fontweight='bold', color='#003366')

        plt.legend(loc='upper right')

        plt.figtext(0.15, 0.01, f"Min Frequency: {min_freq}   |   Max Frequency: {max_freq}",
                    ha='left', fontsize=11, fontweight='bold', color='#006600')

        plt.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = DiceRollingSimulation()
    window.show()
    sys.exit(app.exec_())
