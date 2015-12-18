import sys

modes = { 'AB': 0, 'ABX': 1, 'ABY': 2, 'ACC': 3, 'IMM': 4, 'IN': 5, 'INX': 6, 'INY': 7, 'REL': 8, 'ZP': 9, 'ZPX': 10, 'ZPY': 11, 'IMP': 12 }

def init_mode_LUT():
    hex_mode_LUT = []
    for i in range(256):
        hex_mode_LUT.append(modes['IMM'])
    return hex_mode_LUT
    
def gen_hex_to_func_in_C():
    f = open('opcode-defines.txt', 'r')
    words = []
    for line in f:
        words = line.split()
        if len(words) > 1:
            if '_' in words[1]:
                func_name = words[1].split('_')[0].lower()
            else:
                func_name = words[1].lower()
            sys.stdout.write('hex_func[' + words[2] + '] = \"' + func_name + '\\0\";\n')
    f.close()

def gen_hex_to_mode_LUT():
    hex_mode_LUT = init_mode_LUT()
    f = open('opcode-defines.txt', 'r')
    words = []
    for line in f:
        words = line.split()
        if len(words) > 1:
            if '_' in words[1]:
                hex_mode_LUT[int(words[2], 16)] = modes[words[1].split('_')[1]]
            else:
                hex_mode_LUT[int(words[2], 16)] = modes['IMP']
    f.close()
    return hex_mode_LUT

def print_mode_LUT(LUT_name, LUT):
    sys.stdout.write('MODE ' + LUT_name + '[' + str(len(LUT)) + '] = {\n');
    for i in range(len(LUT)-1):
        if (i+1) % 16 == 0 and i != 0:
            sys.stdout.write('{0:2d}'.format(LUT[i]))
            print(',')
        else:
            sys.stdout.write('{0:2d}'.format(LUT[i]))
            sys.stdout.write(', ')
    sys.stdout.write('{0:2d}'.format(LUT[len(LUT)-1]))
    sys.stdout.write(' };\n')

if __name__ == '__main__':
    hex_mode_LUT = gen_hex_to_mode_LUT()
    print_mode_LUT('HEX_TO_MODE', hex_mode_LUT)
    #gen_hex_to_func_in_C()
