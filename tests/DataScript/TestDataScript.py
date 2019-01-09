import os

os.system("python ../../StockScript.py -r")
os.system("mkdir ../../html")
os.system("cp goog.html ../../html")
os.system("python ../../StockScript.py -p")


