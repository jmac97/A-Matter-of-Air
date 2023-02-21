
import xlrd

book = xlrd.open_workbook("data/poverty_data.xls")
sheet = book.sheet_by_index(0)

poverty_data = 1;

if poverty_data == 1:
   print("{", end='')
   data = sheet.col_values(6)

   for x in range (2, 44):
      if round(data[x]) <= 5.5:
         print("0",end='')
      if round(data[x]) > 5.5 and round(data[x]) <= 11:
         print("1", end='')
      if round(data[x]) > 11 and round(data[x]) <= 16.5:
         print("2", end='')
      if round(data[x]) > 16.5 and round(data[x]) <= 22:
         print("3", end='')
      if round(data[x]) > 22 and round(data[x]) <= 27.5:
         print("4", end='')         
      if round(data[x]) > 27.5 and round(data[x]) <= 33:
         print("5", end='')         
      if round(data[x]) > 33:
         print("6", end='')

      if x != 43:
         print(",", end='')      
   print("}")
else: 
   amountOfData = sheet.row_values(13)

   data = sheet.row_values(1)

   inc_amount = 12
   end_range = 13

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
            # if end_range == 13:
            #    print("0.0, ", end='')
            if inc_amount != 13:
               print(data[y+inc]+3, ",", end='')
         elif y != inc_amount:
            print(data[y+inc]+3, ",", end='')
         elif y == inc_amount:
            print(data[y+inc]+3, end='')
      print("},")
      inc += inc_amount
   print("};")
