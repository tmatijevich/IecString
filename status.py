import csv
import ctypes

InputFile = 'status.csv'

with open(InputFile, mode = 'r', encoding = 'utf-8-sig') as OpenFile:
    DataCSV = csv.reader(OpenFile)
    next(DataCSV)
    for Row in DataCSV:
        if Row[0] == '':
            print('Empty row, conversion aborted')
            break
        EventID = ctypes.c_long((int(Row[0]) << 30) + (1 << 29) + (int(Row[1]) << 16) + int(Row[2]))
        print(Row[3] + ': ' + str(EventID.value))
