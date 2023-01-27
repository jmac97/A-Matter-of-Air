
import xlrd

book = xlrd.open_workbook("data/657_asthma_adl_VisualizeSpaceTimeCube3D1.xls")
sheet = book.sheet_by_index(0)
amountOfData = sheet.row_values(13)

data = sheet.row_values(1)

inc_amount = 0
end_range = 0

print(amountOfData[1])
if amountOfData[1] == 0:
   inc_amount = 12
   end_range = 13
elif amountOfData[1] == 12:
   inc_amount = 13
   end_range = 14
else:
   print("range error")


print("{")
data = sheet.col_values(5)

inc = 0
for x in range(1, 43):
   for y in range(1, end_range):
      if y == 1:
         print("{", end='')
         if end_range == 13:
            print("0.0, ", end='')
         print(data[y+inc]+3, ",", end='')
      elif y != inc_amount:
         print(data[y+inc]+3, ",", end='')
      elif y == inc_amount:
         print(data[y+inc]+3, end='')
   print("},")
   inc += inc_amount
print("};")
