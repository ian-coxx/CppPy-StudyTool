import tkinter as tk
#import sys
#sys.path.append("../studytool.h")
from tkinter import messagebox
#from studytool import StudyTool  # Importing the StudyTool class from studytool.py

try:
    from studytool import StudyTool
except ImportError as e:
    print("Error importing studytool module:", e)

class StudyToolGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("C++ Study Tool")

        self.study_tool = StudyTool()  # Assuming StudyTool class is imported from studytool.py

        self.label = tk.Label(root, text="Enter a term:")
        self.label.pack()

        self.term_entry = tk.Entry(root)
        self.term_entry.pack()

        self.definition_label = tk.Label(root, text="Enter the definition:")
        self.definition_label.pack()

        self.definition_entry = tk.Entry(root)
        self.definition_entry.pack()

        self.add_button = tk.Button(root, text="Add Term", command=self.add_term)
        self.add_button.pack()

        self.play_button = tk.Button(root, text="Play", command=self.start_game)
        self.play_button.pack()

    def add_term(self):
        term = self.term_entry.get()
        definition = self.definition_entry.get()
        self.study_tool.add_term_definition(term, definition)
        messagebox.showinfo("Success", "Term added successfully!")
        self.term_entry.delete(0, tk.END)
        self.definition_entry.delete(0, tk.END)

    def start_game(self):
        # Logic to start the game
        messagebox.showinfo("Game", "Game started!")

if __name__ == "__main__":
    root = tk.Tk()
    app = StudyToolGUI(root)
    root.mainloop()
