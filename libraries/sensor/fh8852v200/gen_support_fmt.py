import sys
import os
import re

tmp_file_name = 'tmp.txt'
doc_dir = '.'
_4line_file_name = 'FH8858V200_Support_Format.md'
_2line_file_name = 'FH8852V200_FH8856V200_Support_Format.md'
_4line_file_name_table = 'FH8858V200_Support_Format_Table.md'
_2line_file_name_table = 'FH8852V200_FH8856V200_Support_Format_Table.md'

support_format = [
    '720P',
    '960P',
    '1080P',
    '1200P',
    '1536X1536P',
    '1536P',
    '400WP',
    '500WP',
    '800WP',
    '2304X1296P',
    '192X192P',
    '384X384P',
    '2688X1520P',
    '2592X1952P',
]

def gen_table(sensor_name, format_list, fps_list, lane_number_list, max_lane):
    out_string = '\n|' + sensor_name + '  |'
    hit_flag = 0
    i = 0
    j = 0
    fps_stack = []

    for total_format in support_format:
        for actual_format in format_list:
            if actual_format.upper() in total_format:
                hit_flag = 1
                if int(lane_number_list[i]) <= max_lane:
                    fps_stack.append(fps_list[i])
            i+=1

        fps_stack = list(set(fps_stack))
        fps_stack.sort()

        for j in range(0, len(fps_stack)):
            out_string += fps_stack[j]
            if j < len(fps_stack) - 1:
                out_string += '/'


        if hit_flag:
            if len(fps_stack) != 0:
                out_string += ' |'
            else:
                out_string += '    x    |'
        else:
            out_string += '    x    |'

        fps_stack = []

        i = 0
        hit_flag = 0

    return out_string

def gen_desc(sensor_name, format_list, fps_list, lane_number_list, max_lane):
    out_string = '## ' + sensor_name + '\n'
    hit_flag = 0
    i = 0
    j = 0
    fps_stack = []

    for total_format in support_format:
        for actual_format in format_list:
            if actual_format.upper() in total_format:
                hit_flag = 1
                if int(lane_number_list[i]) <= max_lane:
                    fps_stack.append(fps_list[i])
            i+=1

        fps_stack = list(set(fps_stack))
        fps_stack.sort()

        if hit_flag:
            if len(fps_stack) != 0:
                out_string += '- ' + total_format + ' '
        for j in range(0, len(fps_stack)):
            out_string += fps_stack[j]
            if j < len(fps_stack) - 1:
                out_string += '/'
            else:
                out_string += '\n'

        fps_stack = []

        hit_flag = 0
        i = 0

    return out_string

def gen_head(file_name):
    with open(file_name, 'w') as outfile:
        out_string = '|    Sensor    |\
    720P    |\
    960P    |\
    1080P    |\
    1200P   |\
    1536x1536   |\
    1536P   |\
    400W    |\
    500W    |\
    800W    |\
    2304x1296    |\
    192x192    |\
    384x384    |\
    2688x1520  |\
    2592x1952    |\n'
        out_string += '| :---------: | :--: | ---- | :------: | :---: | :-------: | :--------------: | :------:  | :--------:  | :--: | :-------: | :-----: | :-----: | :-----: | :-----: |'
        outfile.write(out_string)

if __name__ == '__main__':

    sensor_name = sys.argv[1]


    if sensor_name == 'NULL':
        gen_head(doc_dir + '/' + _4line_file_name_table)
        gen_head(doc_dir + '/' + _2line_file_name_table)
        os.system('rm -rf ' + doc_dir + '/' + _4line_file_name)
        os.system('rm -rf ' + doc_dir + '/' + _2line_file_name)
        sys.exit()

    if sensor_name == 'copy':
        out_string = '# Format Support List\n'
        with open(doc_dir + '/' + _4line_file_name, 'r') as outfile:
            out_string += outfile.read()
            out_string += '\n\n# Format Support Table\n\n'
        with open(doc_dir + '/' + _4line_file_name_table, 'r') as outfile:
            out_string += outfile.read()
        with open(doc_dir + '/' + _4line_file_name, 'w') as outfile:
            outfile.write(out_string)
        out_string = '# Format Support List\n'
        with open(doc_dir + '/' + _2line_file_name, 'r') as outfile:
            out_string += outfile.read()
            out_string += '\n\n# Format Support Table\n\n'
        with open(doc_dir + '/' + _2line_file_name_table, 'r') as outfile:
            out_string += outfile.read()
        with open(doc_dir + '/' + _2line_file_name, 'w') as outfile:
            outfile.write(out_string)
        os.system('rm -rf ' + doc_dir + '/' + _4line_file_name_table)
        os.system('rm -rf ' + doc_dir + '/' + _2line_file_name_table)
        sys.exit()

    if sensor_name == 'dummy_sensor':
        sys.exit()

    os.system('ls cfg > ' + tmp_file_name)

    format_list = []
    fps_list = []
    lane_number_list = []

    format_list_wdr = []
    fps_list_wdr = []
    lane_number_list_wdr = []

    with open(tmp_file_name, 'r') as file:
        for line in file:
            if '.h' not in line:
                continue
            lane_number = re.match('.*_(\d)lane_.*.h', line)
            lane_number = lane_number.group(1)
            format = re.match('.*lane_(.*).h', line)
            format_fps_wdr = format.group(1)
            format = re.match('(\d*x?X?\d*w?p?P?).*', format_fps_wdr)
            format = format.group(1)
            fps = re.match('\d*x?X?\d*w?(\d*)p?P?(\d*).*', format_fps_wdr)
            fps = fps.group(1) + '.' + fps.group(2)
            fps = fps.strip('.')
            wdr_flag = re.findall('wdr', format_fps_wdr)
            if wdr_flag:
                format_list_wdr.append(format)
                fps_list_wdr.append(fps)
                lane_number_list_wdr.append(lane_number)
            else:
                format_list.append(format)
                fps_list.append(fps)
                lane_number_list.append(lane_number)
        with open('../' + doc_dir + '/' + _4line_file_name, 'a') as outfile:
            out_string = ''
            if lane_number_list:
                out_string += gen_desc(sensor_name, format_list, fps_list, lane_number_list, 4)
            if lane_number_list_wdr:
                out_string += gen_desc(sensor_name + '_wdr', format_list_wdr, fps_list_wdr, lane_number_list_wdr, 4)
            outfile.write(out_string)

        with open('../' + doc_dir + '/' + _2line_file_name, 'a') as outfile:
            out_string = ''
            if lane_number_list and '2' in lane_number_list:
                out_string += gen_desc(sensor_name, format_list, fps_list, lane_number_list, 2)
            if lane_number_list_wdr and '2' in lane_number_list_wdr:
                out_string += gen_desc(sensor_name + '_wdr', format_list_wdr, fps_list_wdr, lane_number_list_wdr, 2)
            outfile.write(out_string)


        with open('../' + doc_dir + '/' + _4line_file_name_table, 'a') as outfile:
            out_string = ''
            if lane_number_list:
                out_string += gen_table(sensor_name, format_list, fps_list, lane_number_list, 4)
            if lane_number_list_wdr:
                out_string += gen_table(sensor_name + '_wdr', format_list_wdr, fps_list_wdr, lane_number_list_wdr, 4)
            outfile.write(out_string)

        with open('../' + doc_dir + '/' + _2line_file_name_table, 'a') as outfile:
            out_string = ''
            if lane_number_list and '2' in lane_number_list:
                out_string += gen_table(sensor_name, format_list, fps_list, lane_number_list, 2)
            if lane_number_list_wdr and '2' in lane_number_list_wdr:
                out_string += gen_table(sensor_name + '_wdr', format_list_wdr, fps_list_wdr, lane_number_list_wdr, 2)
            outfile.write(out_string)

    os.system('rm -rf ' + tmp_file_name)