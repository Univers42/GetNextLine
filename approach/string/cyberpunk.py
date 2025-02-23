import os
import time
from typing import List

# ANSI color codes
class Colors:
    RESET = "\033[0m"
    CYAN = "\033[96m"
    MAGENTA = "\033[95m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"

def clear_screen():
    """Clear the terminal screen."""
    os.system('cls' if os.name == 'nt' else 'clear')

def create_frame(matrix_chars: str, width: int, height: int) -> List[str]:
    """
    Create a single frame of the animation.
    matrix_chars: Characters to fall in the matrix
    width: Width of the animation
    height: Height of the animation
    """
    frame = []
    # Create building silhouettes
    for y in range(height):
        line = ""
        for x in range(width):
            # Random chance for buildings
            if x % 5 == 0 and y > height - 5:
                line += f"{Colors.CYAN}█{Colors.RESET}"
            # Falling characters
            elif y > height - 10 and x % 3 == 0:
                line += f"{Colors.GREEN}{matrix_chars[y % len(matrix_chars)]}{Colors.RESET}"
            else:
                line += " "
        frame.append(line)
    return frame

def animate():
    """Main animation loop."""
    matrix_chars = "01@#$%&*!<>+-=/\\|"
    width, height = 60, 20
    frames = []
    
    # Create initial frame
    frames.append(create_frame(matrix_chars, width, height))
    
    try:
        while True:
            clear_screen()
            # Print current frame
            for line in frames[0]:
                print(line)
            
            # Update falling characters
            frames[0] = create_frame(
                matrix_chars,
                width,
                height
            )
            
            # Add subtle flickering effect
            if os.name == 'nt':  # Windows needs shorter delay
                time.sleep(0.05)
            else:
                time.sleep(0.1)
                
    except KeyboardInterrupt:
        print("\nAnimation stopped.")

if __name__ == "__main__":
    animate()