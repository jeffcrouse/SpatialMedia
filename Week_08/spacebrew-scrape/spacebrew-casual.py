#!/usr/bin/python

import time
import locale
from spacebrewInterface.spacebrew import Spacebrew
from lxml.html import parse
from lxml.cssselect import CSSSelector

# configure the spacebrew client
name = "Casual Scraper"
server = "sandbox.spacebrew.cc"
brew = Spacebrew(name, server=server)
brew.addPublisher("tick", "string")
# brew.addSubscriber("incoming", "string")

# def handleString(value):
# 	print(value)

# brew.subscribe("incoming", handleString)

try:
	print("Starting spacebrew");
	brew.start()

	base_urls = [
		"http://newyork.craigslist.org/cas/", 
		"http://philadelphia.craigslist.org/cas/", 
		"http://sfbay.craigslist.org/cas/"]
	links = []
	while 1:
		for base_url in base_urls:
			print "scraping %s" % base_url
			doc = parse(base_url).getroot()
			for link in doc.cssselect('p.row a'):
				if link.get('href') not in links:
					brew.publish('tick', link.text_content())
					links.append( link.get('href') )
					print '%s: %s' % (len(links), link.get('href'))
		time.sleep(2.5)
	
# Catch ctrl+c
except (KeyboardInterrupt, SystemExit):
	print("Exiting!")

# closing out the app and returning terminal to old settings
finally:
	print("Stopping spacebrew");
	brew.stop()

