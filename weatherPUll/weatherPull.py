import urllib2
import json
response = urllib2.urlopen("http://api.wunderground.com/api/98de3a7071959cbd/conditions/q/TX/Dallas.json")
text = response.read()
