import subprocess

program_paths = [
    "avl.out"
]

for program_path in program_paths:
    for _ in range(10000):
        result = subprocess.run(program_path, capture_output=True, text=True)
