from datetime import datetime
date = "2022/2/2"
dweek = datetime.strptime(date, "%Y/%m/%d")
dweek = dweek.strftime("%A")
print(dweek)
e = datetime.datetime(2,2,2,2)