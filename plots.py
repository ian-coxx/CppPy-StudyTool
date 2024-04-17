import pandas as pd
import matplotlib.pyplot as plt

frame = pd.read_csv('../game_sessions.csv')

fig, ax = plt.subplots(figsize=(10, 6))

session_numbers = range(1, len(frame) + 1)
ax.bar(session_numbers, frame['NumCorrectAnswers'], color='skyblue')

ax.set_xlabel('Games Played')
ax.set_ylabel('Score')
ax.set_title('Scores vs. Games Played')

plt.tight_layout()
plt.show()