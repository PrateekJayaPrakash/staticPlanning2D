import os
import pandas as pd
import matplotlib.pyplot as plt

def display_grid_from_csv(csv_file, path_file):
    # Read CSV into DataFrame
    df = pd.read_csv(csv_file)
    
    # Extract grid dimensions
    gridWidth = df['node_x'].max() + 1
    gridHeight = df['node_y'].max() + 1
    
    # Initialize grid
    grid = [[' ' for _ in range(gridWidth)] for _ in range(gridHeight)]
    
    # Fill grid with obstacles
    for index, row in df.iterrows():
        if row['obstacle'] == 1:
            grid[row['node_y']][row['node_x']] = 'X'
        else:
            grid[row['node_y']][row['node_x']] = '.'
    
    # Read path CSV into DataFrame
    path_df = pd.read_csv(path_file)
    
    # Display grid
    plt.figure(figsize=(8, 8))
    for y in range(gridHeight):
        for x in range(gridWidth):
            if grid[y][x] == 'X' or grid[y][x] == '.':
                plt.text(x, y, 'o', ha='center', va='center', color='black', fontsize=8)
            elif [x, y] in path_df[['node_x', 'node_y']].values.tolist():
                plt.plot(x, y, marker='o', color='grey', markersize=8)

    # Plot path with arrows
    for i in range(len(path_df) - 1):
        plt.arrow(path_df.loc[i, 'node_x'], path_df.loc[i, 'node_y'],
                  path_df.loc[i+1, 'node_x'] - path_df.loc[i, 'node_x'],
                  path_df.loc[i+1, 'node_y'] - path_df.loc[i, 'node_y'],
                  head_width=0.1, head_length=0.1, fc='red', ec='red')

    plt.gca().invert_yaxis()  # Invert y-axis to match grid coordinates
    plt.gca().set_aspect('equal', adjustable='box')
    plt.title('Grid with Obstacles and Path')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(False)
    plt.xticks(range(gridWidth))
    plt.yticks(range(gridHeight))
    plt.xlim(-0.5, gridWidth - 0.5)
    plt.ylim(-0.5, gridHeight - 0.5)
    plt.show()

# Get current directory
current_dir = os.getcwd()

# Construct paths to the map and path files
map_file = os.path.join(current_dir, 'output/map.csv')
path_file = os.path.join(current_dir, 'output/path.csv')

# Display grid with path
display_grid_from_csv(map_file, path_file)
