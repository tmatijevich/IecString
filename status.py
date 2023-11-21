# File: status.py
# Created: 2023-04-25
#
# Authors: 
#   Tyler Matijevich
#
# License:
#   This file status.py is part of the IecString project 
#   released under the MIT license agreement.

import csv
import ctypes

csv_file_name = 'status.csv'

with open(csv_file_name, mode = 'r', encoding = 'utf-8-sig') as csv_file_object:
    csv_data = csv.reader(csv_file_object)
    next(csv_data)
    for csv_row in csv_data:
        if csv_row[0] == '':
            print('Empty csv_row, conversion aborted')
            break
        
        event_id = ctypes.c_long(
            (int(csv_row[0]) << 30) +
            (1 << 29) +
            (int(csv_row[1]) << 16) +
            int(csv_row[2]))

        print(csv_row[3] + ': ' + str(event_id.value))
