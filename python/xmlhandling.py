import sys
import xml.etree.ElementTree as ET
#iterate through the entire tree and display all the XML values
def dumpXml(fileName) :
		
	try :
		tree = ET.parse(fileName)
		root = tree.getroot()
		for child in root:
			print(child)
					
	except:
		print("Exception caught: ", sys.exc_info())	
		raise Exception('Failed to parse XML');
	
	return crossPointSuccessResponses


	   






	
	
	
