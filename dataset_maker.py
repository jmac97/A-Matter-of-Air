
import xlrd

book = xlrd.open_workbook("data/365_PM_2_5_Values_VisualizeSpaceTimeCube3D1.xls")
sheet = book.sheet_by_index(0)
amountOfData = sheet.row_values(12)

data = sheet.row_values(1)


if amountOfData[0] == 12:
    print("{")
    data = sheet.col_values(5)

    inc = 0
    for x in range(1, 43):
        for y in range(1, 13):
            if y == 1 or y == 2:
                continue
            else: 
                # print("{")
                if y != 12:
                    if y == 3:
                        print("{", end='')
                    print(data[y+inc], ",", end='')
                else:
                    print(data[y+inc], end='')
        print("},")
        inc += 12
    print("}")