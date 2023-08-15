import os
import matplotlib.pyplot as plt

import random

# Get the size of the file
def get_size(filename):
    st = os.stat(filename)
    return st.st_size

# Get the size of the inputs
def get_input_sizes():
    sizes = []
    for i in range(1, 16):
        size = get_size('inputs/input_' + str(i) + '.txt')
        sizes.append(size)
    return sizes

# Get the size of the compressed files
def get_compressed_sizes():
    sizes = []
    for i in range(1, 16):
        size = get_size('compressedFiles/input_' + str(i) + '.txt.af')
        sizes.append(size)
    return sizes

# find the average compression percentage
def find_average_compression_percentage():
    input_sizes = get_input_sizes()
    compressed_sizes = get_compressed_sizes()
    total = 0
    for i in range(0, len(input_sizes)):
        input_size = input_sizes[i]
        compressed_size = compressed_sizes[i]
        compression_percentage = (input_size - compressed_size) / input_size * 100
        total += compression_percentage
    return round(total / len(input_sizes), 4) 

# Make a table out of the sizes and compare them and write to a file in md format
# include compression percentage
def make_table():
    input_sizes = get_input_sizes()
    compressed_sizes = get_compressed_sizes()
    with open('table.md', 'w') as f:
        f.write('| Input Size | Compressed Size | Compression Percentage |\n')
        f.write('|------------|-----------------|------------------------|\n')
        for i in range(0, len(input_sizes)):
            input_size = input_sizes[i]
            compressed_size = compressed_sizes[i]
            compression_percentage = (input_size - compressed_size) / input_size * 100
            # Convert to KB, MB, GB, TB
            if input_size > 1000000000:
                input_size = str(round(input_size / 1000000000, 4)) + ' TB'
            elif input_size > 1000000:
                input_size = str(round(input_size / 1000000, 4)) + ' GB'
            elif input_size > 1000:
                input_size = str(round(input_size / 1000, 4)) + ' MB'
            else:
                input_size = str(input_size) + ' KB'
            
            if compressed_size > 1000000000:
                compressed_size = str(round(compressed_size / 1000000000, 4)) + ' TB'
            elif compressed_size > 1000000:
                compressed_size = str(round(compressed_size / 1000000, 4)) + ' GB'
            elif compressed_size > 1000:
                compressed_size = str(round(compressed_size / 1000, 4)) + ' MB'
            else:
                compressed_size = str(compressed_size) + ' KB'
            
            f.write('| ' + str(input_size) + ' | ' + str(compressed_size) + ' | ' + str(round(compression_percentage, 4)) + '% |\n')
        f.write('| Average | ' + str(find_average_compression_percentage()) + ' |\n')


# Draw a line graph to file
def draw_graph():
    input_sizes = get_input_sizes()
    compressed_sizes = get_compressed_sizes()
    plt.plot(input_sizes, label='Input Size')
    plt.plot(compressed_sizes, label='Compressed Size')
    plt.legend()
    plt.savefig('graph.png')

# get system details mac
def get_system_details():
    with open('system_details.md', 'w') as f:
        f.write('## System Details\n')
        f.write('### CPU\n')
        f.write('```')
        f.write(os.popen('sysctl -n machdep.cpu.brand_string').read())
        f.write('```\n')
        f.write('### RAM\n')
        f.write('```')
        f.write(os.popen('system_profiler SPHardwareDataType | grep "Memory"').read())
        f.write('```\n')
        f.write('### Disk\n')
        f.write('```')
        f.write(os.popen('system_profiler SPStorageDataType | grep "Capacity"').read())
        f.write('```\n')
        f.write('### OS\n')
        f.write('```')

# Main function
if __name__ == '__main__':
    make_table()
    draw_graph()
    get_system_details()