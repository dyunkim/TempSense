import urllib2
import json
import serial

cities = {}
beijingString = "/q/zmw:00000.1.54511.json"	#Beijing code
dallasString = "TX/Dallas.json"
sydneyString = "Australia/Sydney.json"

cities[beijingString] = ""
cities[dallasString] = ""
cities[sydneyString] = ""

# for x in cities:
# 	url = "http://api.wunderground.com/api/98de3a7071959cbd/conditions/q/"
# 	url += x
# 	response = urllib2.urlopen(url)
# 	jsonObj = json.loads(response.read())
# 	cities[x] = jsonObj["current_observation"]

while True:
	dataList = []
	print "Choose an option!"
	print "[1] Dallas, TX"
	print "[2] Beijing, China"
	print "[3] Sydney, Australia"
	print "[4] Enter a zipcode"
	print "[5] Exit"

	choice = input("Input: ")

	if choice == 1:
		key = dallasString
		dataList.append(cities[key]["feelslike_f"])
		dataList.append(cities[key]["precip_today_in"])
		dataList.append(cities[key]["wind_mph"])
	elif choice == 2:
		key = beijingString
		dataList.append(cities[key]["feelslike_f"])
		dataList.append(cities[key]["precip_today_in"])
		dataList.append(cities[key]["wind_mph"])
	elif choice == 3:
		key = sydneyString
		dataList.append(cities[key]["feelslike_f"])
		dataList.append(cities[key]["precip_today_in"])
		dataList.append(cities[key]["wind_mph"])
	elif choice == 4:
		zipcode = input("Enter Zipcode: ")
		# url = "http://api.wunderground.com/api/98de3a7071959cbd/conditions/q/"
		# url += (str(zipcode) + ".json")
		# response = urllib2.urlopen(url)
		# jsonObj = json.loads(response.read())
		# zipData = jsonObj["current_observation"]
		# print zipData["display_location"]["full"]
		# dataList.append(zipData["feelslike_f"])
		# dataList.append(zipData["precip_today_in"])
		# dataList.append(zipData["wind_mph"])
		dataList = ['65.8', '0.00', 0.3]
		print dataList
	elif choice == 5:
		print "Good Bye!"
		break
	ser = serial.Serial('COM3', 9600)
	for x in dataList:
		serial.write(x)

