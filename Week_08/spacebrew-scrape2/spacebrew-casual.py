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
brew.addPublisher("image", "string")
print("Starting spacebrew");
brew.start()


base_urls = [
	"http://newyork.craigslist.org/cas/", 
	"http://philadelphia.craigslist.org/cas/", 
	"http://sfbay.craigslist.org/cas/"]
history = []
try:
	while 1:
		for base_url in base_urls:
			print "scraping %s" % base_url
			doc = parse(base_url).getroot()
			for link in doc.cssselect('p.row a'):
				subdoc_url = link.get('href')
				subdoc = parse(subdoc_url).getroot()
				images = subdoc.cssselect('img#iwi')
				print "\t%s %d images" % (subdoc_url, len(images))
				for image in images:
					img_url = image.get('src')
					if img_url not in images:
						print "\t\t%s" % (img_url)
						brew.publish('image', img_url)
						history.append( img_url )

		print 'Sent %d images' % len(history)
		time.sleep(2.5)

# closing out the app and returning terminal to old settings
finally:
	print("Stopping spacebrew");
	brew.stop()

