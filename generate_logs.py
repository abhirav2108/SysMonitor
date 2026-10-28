import random

def create_massive_log(filename, num_lines):
    # Standard log messages
    normal_logs = [
        "INFO: Server running smoothly.\n",
        "WARN: Memory usage at 75%.\n",
        "INFO: User authentication successful.\n",
        "INFO: Database query executed in 12ms.\n"
    ]
    
    print(f"Generating {filename} ({num_lines} lines)...")
    
    with open(filename, 'w') as file:
        for _ in range(num_lines):
            # Give a 0.01% chance to write an ERROR line so they are rare
            if random.random() < 0.0001:
                file.write("ERROR: Critical thread crash detected on port 8080.\n")
            else:
                file.write(random.choice(normal_logs))

# Generate 4 massive files (1 million lines each, roughly 45MB per file)
for i in range(1, 5):
    create_massive_log(f"big_log{i}.txt", 1000000)

print("Done! Data is ready for FastSearch.")